# Set the project name

project (ArduinoBackport)

# Add a library with the above sources
file(GLOB source_files
        "TimerHelpers.cpp"
)

file(GLOB header_files
        "TimerHelpers.hpp"
        "ArduMath.hpp"
)

add_library(ArduinoBackport
        ${source_files}
        ${header_files}
)


target_include_directories(ArduinoBackport
        PUBLIC ${PROJECT_SOURCE_DIR}/
)


target_link_libraries(ArduinoBackport PUBLIC Print stm32cubemx)