cmake_minimum_required(VERSION 3.10)
project(TUIForm)

set(CMAKE_CXX_STANDARD 11)

# 让 CMake 生成的可执行文件存放到 bin 目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release)

# 添加可执行文件
add_executable(TUI main.cpp tui_lib.cpp)

# 复制 MinGW 运行时 DLL，确保 EXE 可以运行
if (MINGW)
    set(MINGW_BIN "C:/Program Files/JetBrains/CLion 2024.2.2/bin/mingw/bin")

    add_custom_command(TARGET TUI POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MINGW_BIN}/libstdc++-6.dll"
            "${MINGW_BIN}/libgcc_s_seh-1.dll"
            "${MINGW_BIN}/libwinpthread-1.dll"
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}"
    )
endif()
