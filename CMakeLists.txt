cmake_minimum_required(VERSION 3.16)
project(GuAndroidEmulatorPrototype VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(guemu
    src/main.cpp
    src/config.cpp
    src/rom_manager.cpp
    src/input_mapper.cpp
    src/virtual_device.cpp
)

target_include_directories(guemu PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(guemu_zh
    src/main_zh.cpp
    src/config.cpp
    src/rom_manager.cpp
    src/input_mapper.cpp
    src/virtual_device.cpp
)

target_include_directories(guemu_zh PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (MSVC)
    target_compile_options(guemu PRIVATE /W4 /permissive-)
    target_compile_options(guemu_zh PRIVATE /W4 /permissive-)
else()
    target_compile_options(guemu PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(guemu_zh PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
if (BUILD_TESTING)
    add_executable(guemu_tests
        tests/test_main.cpp
        src/config.cpp
        src/rom_manager.cpp
        src/input_mapper.cpp
        src/virtual_device.cpp
    )
    target_include_directories(guemu_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    add_test(NAME guemu_tests COMMAND guemu_tests)
endif()
