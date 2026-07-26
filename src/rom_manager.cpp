#include "rom_manager.h"

#include <fstream>
#include <stdexcept>

namespace guemu {

RomManager::RomManager(Paths paths) : paths_(std::move(paths)) {
    std::filesystem::create_directories(paths_.romStore);
    std::filesystem::create_directories(paths_.instanceStore);
}

std::filesystem::path RomManager::manifestPath(const std::string& id) const {
    return paths_.romStore / (id + ".manifest");
}

RomPackage RomManager::createStableGsiGmsTemplate(const std::string& id, const std::string& androidVersion) {
    auto image = paths_.romStore / (id + ".img.placeholder");
    std::ofstream imageOut(image);
    imageOut << "Placeholder for a legally obtained Android GSI + GMS system image.\n";
    imageOut << "Replace this file through import-rom with a downloaded ROM package.\n";
    imageOut.close();

    RomPackage rom{id, "Stable GSI + GMS " + androidVersion, androidVersion, true, true, image};
    std::ofstream manifest(manifestPath(id));
    manifest << rom.id << '\n' << rom.name << '\n' << rom.androidVersion << '\n'
             << rom.includesGms << '\n' << rom.basedOnGsi << '\n' << rom.imagePath.string() << '\n';
    return rom;
}

RomPackage RomManager::importRom(const std::filesystem::path& sourceImage, const std::string& id, const std::string& name) {
    if (!std::filesystem::exists(sourceImage)) {
        throw std::runtime_error("ROM image does not exist: " + sourceImage.string());
    }
    std::filesystem::create_directories(paths_.romStore);
    auto target = paths_.romStore / (id + sourceImage.extension().string());
    std::filesystem::copy_file(sourceImage, target, std::filesystem::copy_options::overwrite_existing);
    RomPackage rom{id, name, "user-imported", true, true, target};
    std::ofstream manifest(manifestPath(id));
    manifest << rom.id << '\n' << rom.name << '\n' << rom.androidVersion << '\n'
             << rom.includesGms << '\n' << rom.basedOnGsi << '\n' << rom.imagePath.string() << '\n';
    return rom;
}

std::vector<RomPackage> RomManager::listRoms() const {
    std::vector<RomPackage> result;
    if (!std::filesystem::exists(paths_.romStore)) {
        return result;
    }
    for (const auto& entry : std::filesystem::directory_iterator(paths_.romStore)) {
        if (entry.path().extension() != ".manifest") {
            continue;
        }
        std::ifstream manifest(entry.path());
        RomPackage rom;
        manifest >> rom.id;
        manifest.ignore();
        std::getline(manifest, rom.name);
        std::getline(manifest, rom.androidVersion);
        manifest >> rom.includesGms >> rom.basedOnGsi;
        std::string image;
        manifest >> image;
        rom.imagePath = image;
        result.push_back(rom);
    }
    return result;
}

std::filesystem::path RomManager::createInstance(const std::string& instanceName, const std::string& romId) const {
    auto instancePath = paths_.instanceStore / instanceName;
    std::filesystem::create_directories(instancePath);
    std::ofstream config(instancePath / "instance.conf");
    config << "rom=" << romId << '\n';
    config << "system_mode=writable_overlay\n";
    config << "root=enabled\n";
    return instancePath;
}

} // namespace guemu
