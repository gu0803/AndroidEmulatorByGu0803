#include "config.h"
#include "input_mapper.h"
#include "rom_manager.h"
#include "virtual_device.h"

#include <exception>
#include <iostream>

using namespace guemu;

int main(int argc, char** argv) {
    try {
        const auto paths = defaultPaths(std::filesystem::current_path() / ".guemu");
        RomManager roms(paths);

        if (argc >= 2 && std::string(argv[1]) == "import-rom" && argc == 5) {
            auto rom = roms.importRom(argv[2], argv[3], argv[4]);
            std::cout << "已导入 ROM：" << rom.name << "，ID：" << rom.id << '\n';
            return 0;
        }
        if (argc >= 2 && std::string(argv[1]) == "create-template-rom") {
            auto rom = roms.createStableGsiGmsTemplate("stable-gsi-gms", "Android 15 stable");
            std::cout << "已创建可导入的 ROM 模板：" << rom.imagePath << '\n';
            return 0;
        }

        auto rom = roms.createStableGsiGmsTemplate("stable-gsi-gms", "Android 15 stable");
        roms.createInstance("tablet-default", rom.id);

        EmulatorSettings settings;
        InputMapper mapper;
        mapper.addTapMapping("W", {1280, 620});
        mapper.addTapMapping("SPACE", {2100, 1380});
        mapper.addLookMapping("RIGHT_MOUSE", {1280, 800}, 500);

        VirtualDevice device(settings, rom);
        device.setGyroscope({0.0, 0.0, 9.8});

        std::cout << "Gu 安卓模拟器原型\n";
        std::cout << device.status() << "\n";
        std::cout << "按键映射：\n" << mapper.serialize();
        std::cout << "提示：此原型会准备 ROM/实例元数据和 QEMU 启动计划；启动前请导入已获得授权的 GSI+GMS 镜像。\n";
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "guemu: " << ex.what() << '\n';
        return 1;
    }
}
