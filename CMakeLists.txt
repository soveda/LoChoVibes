cmake_minimum_required(VERSION 3.13)

# ============================================================
# Raspberry Pi Pico SDK
# ============================================================

if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)

if(DEFINED ENV{PICO_SDK_PATH} AND NOT EXISTS "$ENV{PICO_SDK_PATH}/pico_sdk_init.cmake")
    unset(ENV{PICO_SDK_PATH})
endif()

set(PICO_SDK_CANDIDATES
    ${CMAKE_CURRENT_LIST_DIR}/../pico-sdk
    ${CMAKE_CURRENT_LIST_DIR}/../pico-sdk-src
    ${USERHOME}/pico-sdk
    /opt/pico-sdk)

if(NOT DEFINED ENV{PICO_SDK_PATH} AND NOT PICO_SDK_PATH)
    foreach(candidate ${PICO_SDK_CANDIDATES})
        if(EXISTS ${candidate}/pico_sdk_init.cmake)
            set(PICO_SDK_PATH ${candidate} CACHE PATH "Path to the Raspberry Pi Pico SDK" FORCE)
            break()
        endif()
    endforeach()
endif()

if(NOT DEFINED ENV{PICO_SDK_PATH} AND NOT PICO_SDK_PATH)
    set(PICO_SDK_FETCH_FROM_GIT ON CACHE BOOL "Fetch Raspberry Pi Pico SDK when no local SDK is available" FORCE)
    set(PICO_SDK_FETCH_FROM_GIT_TAG ${sdkVersion} CACHE STRING "Raspberry Pi Pico SDK git tag" FORCE)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/pico_sdk_import.cmake)

# ============================================================
# Project
# ============================================================

project(LoChoVibes C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# ============================================================
# Initialise Pico SDK
# ============================================================

pico_sdk_init()

# ============================================================
# Executable
# ============================================================

add_executable(LoChoVibes
    LoChoVibes.cpp
)

# ============================================================
# Include paths
# ============================================================

target_include_directories(LoChoVibes PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# ============================================================
# Libraries required by ComputerCard
# ============================================================

target_link_libraries(LoChoVibes
    pico_stdlib
    pico_unique_id

    hardware_adc
    hardware_pwm
    hardware_dma
    hardware_spi
    hardware_clocks
    hardware_flash
    hardware_i2c
)

# ============================================================
# Optimisation
# ============================================================

target_compile_options(LoChoVibes PRIVATE
    -O3
    -ffast-math
)

# ============================================================
# Create UF2/BIN/etc
# ============================================================

pico_add_extra_outputs(LoChoVibes)
