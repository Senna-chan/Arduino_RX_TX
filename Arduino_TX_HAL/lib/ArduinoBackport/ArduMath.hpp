#ifndef __ARDUMATH_H
#define __ARDUMATH_H

#include <type_traits>
#include <stdint.h>

template<
    typename T, //real type
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
T map(T x, T in_min, T in_max, T out_min, T out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet((value), (bit)) : bitClear((value), (bit) ))

// template<
//     typename T, //real type
//     typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
// >
// bool bitRead(T val, uint64_t bit) {
//     return (val >> bit) & 0x01;
// }

// template<
//     typename T, //real type
//     typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
// >
// void bitSet(T val, uint64_t bit){
//     val |= (1UL << (bit));
// }

// template<
//     typename T, //real type
//     typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
// >
// void bitClear(T val, uint64_t bit) {
//     val &= ~(1UL << bit);
// }

// template<
//     typename T, //real type
//     typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
// >
// void bitWrite(T val, uint64_t bit, bool bitvalue){
//     if(bitvalue) {
//         bitSet(val, bit);
//     } else {
//         bitClear(val, bit);
//     }
// }

template<
    typename T, //real type
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
T constrain(T val, T min, T max){
    if(val < min) return min;
    if(val > max) return max;
    return val;
}

template<
    typename T, //real type
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
bool between(T val, T min, T max){
    if(val >= min && val <= max) return true;
    return false;
}

#endif
