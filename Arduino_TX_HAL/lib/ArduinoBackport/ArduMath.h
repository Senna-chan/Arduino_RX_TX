#ifndef __MATH_H
#define __MATH_H

long map(long x, long in_min, long in_max, long out_min, long out_max);
#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

template<typename T>
bool bitRead(T val, uint64_t bit) {
    return (((val) >> (bit)) & 0x01);
}

template<typename T>
void bitSet(T val, uint64_t bit){
    ((val) |= (1UL << (bit)));
}

template<typename T>
void bitClear(T val, uint64_t bit) {
    ((val) &= ~(1UL << (bit)));
}

template<typename T>
void bitWrite(T val, uint64_t bit, bool bitvalue){
     ((bitvalue) ? bitSet((val), (bit)) : bitClear((val), (bit) ));
}

#endif
