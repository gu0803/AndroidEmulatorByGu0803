#pragma once

#include "config.h"

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace guemu {

struct RomPackage {
    std::string id;
    std::string name;
    std::string androidVersion;
    bool includesGms = true;
    bool basedOnGsi = true;
    std::filesystem::path imagePath;
};

class RomManager {
public:
    explicit RomManager(Paths paths);

    RomPackage createStableGsiGmsTemplate(const std::string& id, const std::string& androidVersion);
    RomPackage importRom(const std::filesystem::path& sourceImage, const std::string& id, const std::string& name);
    std::vector<RomPackage> listRoms() const;
    std::filesystem::path createInstance(const std::string& instanceName, const std::string& romId) const;

private:
    Paths paths_;
    std::filesystem::path manifestPath(const std::string& id) const;
};

} // namespace guemu
