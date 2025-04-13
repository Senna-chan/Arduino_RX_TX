#ifndef _COMPANIONCONTROL_h
#define _COMPANIONCONTROL_h

#include <functional>
#include <main.h>

struct CC_DataFunctions {
    std::function<int()> available;
    std::function<int()> readSingle;
    std::function<int(uint8_t* buffer, size_t length)> read;
    std::function<int(uint8_t* buffer, size_t length)> write;
};

// This is a FREERTOS Task
void handleCompanionControl(void* parameter);

#endif
