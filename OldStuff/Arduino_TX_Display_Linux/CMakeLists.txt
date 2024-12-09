cmake_minimum_required(VERSION 3.19.1)

project(Ardu_TX_HMI_Linux)

enable_language(CXX)

set(EXEC "Ardu_TX_HMI_Linux")

# Common source files
SET(COMMON_SOURCE_FILES
"${CMAKE_CURRENT_SOURCE_DIR}/Arduino_TX_Display_Linux.c"
"${CMAKE_CURRENT_SOURCE_DIR}/serial.c"
)

add_subdirectory(GUISlice)

# Adding source files to the executable (target).
add_executable(${EXEC} ${COMMON_SOURCE_FILES})

set_property(TARGET ${EXEC} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${EXEC} PROPERTY CXX_STANDARD_REQUIRED On)
set_property(TARGET ${EXEC} PROPERTY CXX_EXTENSIONS Off)

target_include_directories(${EXEC} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/"
)

# # Setup compiler options
target_compile_options(${EXEC} PRIVATE
    "$<$<CONFIG:Debug>:-O0>"
    "$<$<CONFIG:Debug>:-ggdb>"
    "$<$<CONFIG:Release>:-O3>"
    "-Wall"
    "-Wextra"
    "-Wshadow"
    "-fno-exceptions"
    "-Wno-format-truncation"
)

target_link_libraries(${EXEC} PRIVATE GUISlice)