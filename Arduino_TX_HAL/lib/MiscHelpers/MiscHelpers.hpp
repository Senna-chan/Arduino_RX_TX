#ifndef _MISC_HELPERS_HPP
#define _MISC_HELPERS_HPP

#include <type_traits>
#include <bit>
#include <stdint.h>
#include <ArduMath.hpp>
template<
    typename T, //real type
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
void printBits(T var, bool newLine = false) {
    uint32_t i;
    auto bitAmount = sizeof(var) * 8;
	for (i = 0; i < bitAmount; i++) {
		printf(bitRead(var,i) ? "1" : "0");
	}
	if (newLine){
		printf("\n");
    }
}

#endif
