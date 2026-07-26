#include "config.h"
#include "input_mapper.h"
#include "rom_manager.h"
#include "virtual_device.h"

#include <cassert>
#include <filesystem>
#include <iostream>

using namespace guemu;

int main() {
    auto base = std::filesystem::temp_directory_path() / "guemu_tests";
    std::filesystem::remove_all(base);
    RomManager manager(defaultPaths(base));
    auto rom = manager.createStableGsiGmsTemplate("stable", "Android 15 stable");
    assert(rom.includesGms);
    assert(rom.basedOnGsi);
    assert(!manager.listRoms().empty());

    auto instance = manager.createInstance("one", rom.id);
    assert(std::filesystem::exists(instance / "instance.conf"));

    InputMapper mapper;
    mapper.addTapMapping("A", {10, 20});
    mapper.addLookMapping("MOUSE2", {100, 200}, 300);
    assert(mapper.resolve("A")->touch.x == 10);
    assert(mapper.resolve("MOUSE2")->locksMouse);
    assert(!mapper.resolve("B").has_value());

    EmulatorSettings settings;
    VirtualDevice device(settings, rom);
    auto launch = device.buildQemuCommandLine();
    assert(launch.find("qemu-system-x86_64") != std::string::npos);
    assert(launch.find("virtio-gpu-gl") != std::string::npos);

    std::filesystem::remove_all(base);
    std::cout << "all tests passed\n";
    return 0;
}
