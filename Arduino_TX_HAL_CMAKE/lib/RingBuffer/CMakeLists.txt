# Set the project name
#add_library(RingBuffer INTERFACE RingBuffer.hpp)
#target_include_directories(RingBuffer INTERFACE ${PROJECT_SOURCE_DIR})
cmake_minimum_required(VERSION 3.12)

project("RingBuffer")

add_library(RingBuffer INTERFACE)

# Adding the install interface generator expression makes sure that the include
# files are installed to the proper location (provided by GNUInstallDirs)
target_include_directories(RingBuffer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/)