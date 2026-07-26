# Architecture

## Host launcher

`guemu` is the host-side executable. It owns configuration, ROM import, instance creation, input mapping, gyroscope state, and QEMU command-line generation.

## ROM model

ROMs are stored below `.guemu/roms` with a small manifest next to the image. The default template is labelled as a stable GSI + GMS ROM, but only a placeholder is generated so users can import a legally obtained image.

## Instance model

Instances live below `.guemu/instances`. Each instance references a ROM id and uses a writable overlay policy so system changes can be isolated per instance while preserving the base ROM package.

## Rendering plan

The prototype selects a Vulkan-preferred renderer and emits a `virtio-gpu-gl` QEMU launch plan. A production version should probe host support for Vulkan 1.4 and OpenGL ES 3.2 or newer before enabling advanced rendering paths.

## Input plan

`InputMapper` maps host keys to touch coordinates. Look mappings lock a mouse/key input to a center point and radius so first-person camera gestures can be generated inside Android games. Unmapped input can be passed through when enabled in settings.

## Sensor plan

`VirtualDevice::setGyroscope` stores external gyroscope samples. A production device bridge can feed those samples into Android sensor HAL or an emulator console channel.
