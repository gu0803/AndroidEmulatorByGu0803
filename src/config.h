#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace guemu {

struct EmulatorSettings {
    std::string deviceProfile = "tablet";
    bool rootEnabled = true;
    bool writableSystem = true;
    bool passthroughUnmappedInput = true;
    bool armTranslation = true;
    std::string renderer = "vulkan-preferred";
    int requestedVulkanMajor = 1;
    int requestedVulkanMinor = 4;
    int requestedGlesMajor = 3;
    int requestedGlesMinor = 2;
    int width = 2560;
    int height = 1600;
    int dpi = 320;
};

struct Paths {
    std::filesystem::path home;
    std::filesystem::path romStore;
    std::filesystem::path instanceStore;
};

Paths defaultPaths(const std::filesystem::path& base);
std::string describeSettings(const EmulatorSettings& settings);

} // namespace guemu
