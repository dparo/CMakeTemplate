// SPDX-FileCopyrightText: 2023 Davide Paro
//
// SPDX-License-Identifier: MIT

#pragma once

#include <hedley.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define BUILTIN_IS_CONSTANT(x) HEDLEY_IS_CONSTANT(x)
#define BUILTIN_ALWAYS_INLINE HEDLEY_ALWAYS_INLINE

#if __cplusplus
extern "C" {
#endif
typedef char *mutcstr_t;
typedef char const *cstr_t;

typedef uintptr_t ptr_t;
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

typedef float f32_t;
typedef double f64_t;

#define PTR(p) ((uintptr_t)(p))
#define UINTPTR(p) ((uintptr_t)(p))

#if __cplusplus
}
#endif
