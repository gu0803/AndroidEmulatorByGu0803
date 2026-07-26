# Gu 安卓模拟器原型

Gu Android Emulator Prototype 是一个使用 C++17 编写的安卓模拟器主控启动器原型，目标是提供类似商业安卓模拟器的基础管理能力，但不复制任何第三方模拟器代码或资源。

当前版本重点实现：

- ROM 包管理与导入。
- 多实例元数据创建。
- 默认平板配置、root 开启和可写 system overlay 策略。
- 按键映射与鼠标锁定视角映射基础结构。
- 虚拟陀螺仪状态注入接口。
- QEMU/virtio GPU 启动计划生成。
- Windows x64 构建脚本和 GitHub Actions 产物上传。

> 注意：仓库不会内置 Android 系统镜像、Google 服务组件、专有 ARM 转译库或商业驱动。请自行导入合法获取的 GSI + GMS 镜像。

## 构建

```bash
cmake -S . -B build
cmake --build build
```

中文输出版本会生成 `guemu_zh`；Windows x64 构建时会生成 `guemu_zh.exe`。

## Windows x64 构建

在 Visual Studio Developer Command Prompt 中运行：

```bat
scripts\build_win64.bat
```

也可以使用 GitHub Actions 的 `guemu-win64` artifact 下载 Windows x64 程序。

## 使用示例

创建默认 ROM 模板和默认实例：

```bash
./build/guemu_zh
```

创建 GSI + GMS ROM 模板：

```bash
./build/guemu_zh create-template-rom
```

导入你已经下载并合法获取的 ROM 镜像：

```bash
./build/guemu_zh import-rom /path/to/system.img my-rom "我的 GSI + GMS ROM"
```
