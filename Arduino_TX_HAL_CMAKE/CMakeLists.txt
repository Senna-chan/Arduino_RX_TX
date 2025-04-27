cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Arduino_TX_HAL)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(CXX ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(lib/ArduinoBackport)
add_subdirectory(lib/RingBuffer)
add_subdirectory(lib/HardwareSerial)
add_subdirectory(lib/Print)
add_subdirectory(lib/w25qxx)

# Add STM32CubeMX generated sources

#FreeRTOS
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM
        INTERFACE
        ${CMAKE_SOURCE_DIR}/include) # The config file directory

set(FREERTOS_HEAP "${CMAKE_SOURCE_DIR}/src/heap_useNewlib_ST.c" CACHE STRING "" FORCE)
set(FREERTOS_PORT "GCC_ARM_CM4F" CACHE STRING "" FORCE)
# Select the native compile PORT
#set(FREERTOS_PORT "TEMPLATE" CACHE STRING "" FORCE)
add_subdirectory(lib/FreeRTOS)
#end FreeRTOS

add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths

)


FILE(GLOB_RECURSE app_sources CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*")
FILE(GLOB_RECURSE lib_files CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/lib/*.cpp")

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
        ${app_source}
        ${lib_files}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        include/
        lib/AUXSerialReader
        lib/channelfunctions
        lib/CompanionControl
        lib/I2CEncoder
        lib/I2CHelpers
        lib/IBUS
        lib/LoggerLib/src
        lib/MCP23017
        lib/MiscHelpers
        lib/nrf24l01
        lib/PlotterLib/src
        lib/SerialControlLibrary/src
        lib/SettingsHelper
        lib/SharedCode
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
        freertos_kernel
#        Print
#        Serial
        stm32cubemx
    # Add user defined libraries
)
