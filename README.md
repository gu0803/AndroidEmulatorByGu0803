# Gu Android Emulator Prototype

This repository contains a C++17 prototype for a MuMuPlayer-inspired Android emulator launcher. It does not copy MuMuPlayer code or assets. The prototype focuses on the host-side architecture needed to manage ROM packages, create isolated emulator instances, prepare root/writable-system settings, describe input mapping, accept virtual gyroscope state, and generate a QEMU-based launch plan.


## Planned capabilities

- Multi-ROM management with importable ROM packages.
- Stable Android GSI + GMS ROM template metadata. Users must provide legally licensed system images; the repository only creates placeholders.
- Tablet-first defaults: 2560x1600, 320 DPI, root enabled, writable system overlay enabled.
- ARM translation flag for native-like Android-on-QEMU deployments.
- Vulkan-preferred / OpenGL ES 3.2+ rendering intent through virtio GPU OpenGL acceleration.
- Keyboard, mouse, and game-control mapping primitives, including tap mappings and mouse-lock look-area mappings.
- Optional pass-through for unmapped input.
- External virtual gyroscope sample injection API.

## Build

```bash
cmake -S . -B build
cmake --build build
```

The produced executable is `build/guemu` on Linux/macOS. For a Windows 64-bit executable, run `scripts\build_win64.bat` from a Visual Studio Developer Command Prompt; it produces `build-win64\Release\guemu.exe`. From Linux with MinGW-w64 x86_64 installed, run `scripts/build_win64_mingw.sh` to produce `build-win64/guemu.exe`.

## Usage examples

Create a placeholder ROM package and default instance:

```bash
./build/guemu
```

Create only the stable GSI + GMS ROM template:

```bash
./build/guemu create-template-rom
```

Import a downloaded ROM image:

```bash
./build/guemu import-rom /path/to/system.img my-rom "My GSI + GMS ROM"
```

## Important limitations

This is an initial prototype, not a production emulator. It does not bundle Android, Google apps, proprietary ARM translation libraries, Vulkan drivers, or a hypervisor. Production use would require legally distributable ROM packaging, a full QEMU/virtio integration layer, graphics backend validation, device bridge tooling, and platform-specific installers.

## Windows builds

This project includes a GitHub Actions workflow that sets up an MSVC x64 environment on `windows-latest`, configures with Ninja, runs the tests, and uploads `guemu.exe` as the `guemu-win64` artifact. This is the recommended path when you do not have a local Linux environment.

## 简体中文说明

Gu Android Emulator Prototype 是一个使用 C++17 编写的安卓模拟器主控启动器原型，目标是提供类似商业安卓模拟器的基础管理能力，但不复制任何第三方模拟器代码或资源。当前版本重点实现 ROM 包管理、多实例配置、root/可写 system 设置、按键映射、虚拟陀螺仪状态以及 QEMU 启动计划生成。

注意：仓库不会内置 Android 系统镜像、Google 服务组件、专有 ARM 转译库或商业驱动。请自行导入合法获取的 GSI + GMS 镜像。

### 中文界面

程序支持简体中文输出。可以通过命令行参数或环境变量启用：

```bash
./build/guemu --lang zh-CN
GUEMU_LANG=zh-CN ./build/guemu
```

Windows PowerShell 示例：

```powershell
$env:GUEMU_LANG = "zh-CN"
.\guemu.exe
```
