// SPDX-FileCopyrightText: 2023 Davide Paro
//
// SPDX-License-Identifier: MIT

#pragma once

#include <hedley.h>
#include <stddef.h>
#include <stdint.h>

#define BUILTIN_IS_CONSTANT(x) HEDLEY_IS_CONSTANT(x)

#if __cplusplus
extern "C" {
#endif

typedef uint8_t byte_t;
typedef uint8_t byte8_t;
typedef int8_t i8_t;
typedef uint8_t u8_t;
typedef int16_t i16_t;
typedef uint16_t u16_t;
typedef int32_t i32_t;
typedef uint32_t u32_t;
typedef int64_t i64_t;
typedef uint64_t u64_t;

typedef uint8_t B8;
typedef int8_t I8;
typedef uint8_t U8;
typedef int16_t I16;
typedef uint16_t U16;
typedef int32_t I32;
typedef uint32_t U32;
typedef int64_t I64;
typedef uint64_t U64;

#if __cplusplus
}
#endif
