#include "virtual_device.h"

#include <sstream>

namespace guemu {

VirtualDevice::VirtualDevice(EmulatorSettings settings, RomPackage rom)
    : settings_(std::move(settings)), rom_(std::move(rom)) {}

void VirtualDevice::setGyroscope(GyroscopeSample sample) {
    gyro_ = sample;
}

std::string VirtualDevice::buildQemuCommandLine() const {
    std::ostringstream cmd;
    cmd << "qemu-system-x86_64 -enable-kvm -machine q35,accel=kvm:tcg -m 4096 "
        << "-device virtio-gpu-gl -display sdl,gl=on "
        << "-drive if=virtio,format=raw,file=" << rom_.imagePath.string() << ' ';
    if (settings_.writableSystem) {
        cmd << "-snapshot ";
    }
    if (settings_.armTranslation) {
        cmd << "-cpu host,+ssse3,+sse4.2 ";
    }
    return cmd.str();
}

std::string VirtualDevice::status() const {
    std::ostringstream out;
    out << "ROM " << rom_.name << " (" << rom_.androidVersion << ")\n"
        << describeSettings(settings_) << "\n"
        << "gyro=(" << gyro_.x << ',' << gyro_.y << ',' << gyro_.z << ")\n"
        << "launch=" << buildQemuCommandLine();
    return out.str();
}

} // namespace guemu
