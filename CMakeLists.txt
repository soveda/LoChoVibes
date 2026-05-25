cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(locho_vibes)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(locho_vibes
    locho_vibes.cpp
)

target_include_directories(locho_vibes PRIVATE
    ../../Demonstrations+HelloWorlds/PicoSDK/ComputerCard
)

target_compile_options(locho_vibes PRIVATE
    -Wall
    -Wextra
    -Wdouble-promotion
    -Wfloat-conversion
)

target_compile_definitions(locho_vibes PRIVATE
    PICO_XOSC_STARTUP_DELAY_MULTIPLIER=64
)

target_link_libraries(locho_vibes
    pico_stdlib
    pico_unique_id
    hardware_adc
    hardware_dma
    hardware_pwm
    hardware_spi
    hardware_i2c
)

# Strongly recommended for Workshop Computer timing stability.
# Running entirely from RAM avoids flash cache timing jitter.
pico_set_binary_type(locho_vibes copy_to_ram)

# USB stdio interferes with the normalisation probe system.
pico_enable_stdio_usb(locho_vibes 0)
pico_enable_stdio_uart(locho_vibes 0)

pico_add_extra_outputs(locho_vibes)