# Set the project name

project (Serial)

# Add a library with the above sources
file(GLOB source_files
        "src/BaseSerial.cpp"
        "src/HardwareSerial.cpp"
        "src/USBSerial.cpp"
)
file(GLOB header_files
        "inc/BaseSerial.h"
        "inc/HardwareSerial.h"
        "inc/USBSerial.h"
)
add_library(Serial
        ${source_files}
        ${header_files}
)


target_include_directories(Serial
        PUBLIC ${PROJECT_SOURCE_DIR}/inc
)


target_link_libraries(Serial PUBLIC Print stm32cubemx freertos_kernel RingBuffer ArduinoBackport)