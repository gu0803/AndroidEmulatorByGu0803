#include "config.h"
#include "input_mapper.h"
#include "rom_manager.h"
#include "virtual_device.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace guemu;

namespace {

bool startsWith(const std::string& value, const std::string& prefix) {
    return value.rfind(prefix, 0) == 0;
}

bool wantsSimplifiedChinese(const std::vector<std::string>& args) {
    for (std::size_t i = 0; i + 1 < args.size(); ++i) {
        if (args[i] == "--lang") {
            return args[i + 1] == "zh-CN" || args[i + 1] == "zh";
        }
    }
    if (const char* env = std::getenv("GUEMU_LANG")) {
        const std::string lang(env);
        return startsWith(lang, "zh_CN") || startsWith(lang, "zh-CN") || lang == "zh";
    }
    if (const char* env = std::getenv("LANG")) {
        const std::string lang(env);
        return startsWith(lang, "zh_CN") || startsWith(lang, "zh-CN");
    }
    return false;
}

std::vector<std::string> collectCommandArgs(int argc, char** argv) {
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) {
        const std::string arg(argv[i]);
        if (arg == "--lang" && i + 1 < argc) {
            ++i;
            continue;
        }
        args.push_back(arg);
    }
    return args;
}

} // namespace

int main(int argc, char** argv) {
    try {
        const std::vector<std::string> rawArgs(argv + 1, argv + argc);
        const bool zh = wantsSimplifiedChinese(rawArgs);
        const auto args = collectCommandArgs(argc, argv);
        const auto paths = defaultPaths(std::filesystem::current_path() / ".guemu");
        RomManager roms(paths);

        if (args.size() == 4 && args[0] == "import-rom") {
            auto rom = roms.importRom(args[1], args[2], args[3]);
            std::cout << (zh ? "已导入 ROM：" : "Imported ROM: ") << rom.name
                      << (zh ? "，ID：" : " as ") << rom.id << '\n';
            return 0;
        }
        if (!args.empty() && args[0] == "create-template-rom") {
            auto rom = roms.createStableGsiGmsTemplate("stable-gsi-gms", "Android 15 stable");
            std::cout << (zh ? "已创建可导入的 ROM 模板：" : "Created importable ROM template: ")
                      << rom.imagePath << '\n';
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

        std::cout << (zh ? "Gu 安卓模拟器原型\n" : "Gu Android Emulator prototype\n");
        std::cout << device.status() << "\n";
        std::cout << (zh ? "按键映射：\n" : "Mappings:\n") << mapper.serialize();
        std::cout << (zh
            ? "提示：此原型会准备 ROM/实例元数据和 QEMU 启动计划；启动前请导入已获得授权的 GSI+GMS 镜像。\n"
            : "Note: this prototype prepares ROM/instance metadata and a QEMU launch plan; bundle a licensed GSI+GMS image before booting.\n");
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "guemu: " << ex.what() << '\n';
        return 1;
    }
}
