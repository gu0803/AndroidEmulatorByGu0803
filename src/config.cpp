#include "config.h"

#include <sstream>

namespace guemu {

Paths defaultPaths(const std::filesystem::path& base) {
    return Paths{base, base / "roms", base / "instances"};
}

std::string describeSettings(const EmulatorSettings& settings) {
    std::ostringstream out;
    out << "profile=" << settings.deviceProfile
        << ", root=" << (settings.rootEnabled ? "on" : "off")
        << ", writable_system=" << (settings.writableSystem ? "on" : "off")
        << ", input_passthrough=" << (settings.passthroughUnmappedInput ? "on" : "off")
        << ", arm_translation=" << (settings.armTranslation ? "on" : "off")
        << ", renderer=" << settings.renderer
        << ", vulkan=" << settings.requestedVulkanMajor << '.' << settings.requestedVulkanMinor
        << ", gles=" << settings.requestedGlesMajor << '.' << settings.requestedGlesMinor
        << ", resolution=" << settings.width << 'x' << settings.height
        << ", dpi=" << settings.dpi;
    return out.str();
}

} // namespace guemu
