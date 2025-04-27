# Set the project name

project (Print)

# Add a library with the above sources

add_library(Print
        "Print.cpp"
)

target_include_directories( Print
        PUBLIC ${PROJECT_SOURCE_DIR}
)

target_link_libraries(Print PUBLIC stm32cubemx freertos_kernel)