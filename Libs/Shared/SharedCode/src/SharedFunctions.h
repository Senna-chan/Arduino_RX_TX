#ifndef __SHAREDFUNCTIONS_H
#define __SHAREDFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h>
#include <stdint.h>
uint16_t gencrc(uint8_t* data, size_t len);

#ifdef __cplusplus
}
#endif


#endif
