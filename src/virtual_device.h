#pragma once

#include "config.h"
#include "input_mapper.h"
#include "rom_manager.h"

#include <string>

namespace guemu {

struct GyroscopeSample {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

class VirtualDevice {
public:
    VirtualDevice(EmulatorSettings settings, RomPackage rom);
    void setGyroscope(GyroscopeSample sample);
    std::string buildQemuCommandLine() const;
    std::string status() const;

private:
    EmulatorSettings settings_;
    RomPackage rom_;
    GyroscopeSample gyro_;
};

} // namespace guemu
