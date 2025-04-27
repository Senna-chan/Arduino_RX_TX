# Set the project name

project (W25Qxx)

# Add a library with the above sources

file(GLOB source_files
    "w25qxx.cpp"
)

file(GLOB header_files
     "w25qxx.hpp"
     "w25qxxConf.h"
)

add_library(W25Qxx
        ${source_files}
        ${header_files}
)

target_include_directories(W25Qxx
        PUBLIC ${PROJECT_SOURCE_DIR}
)

target_link_libraries(W25Qxx PUBLIC stm32cubemx)
target_compile_features(W25Qxx PUBLIC cxx_std_23)