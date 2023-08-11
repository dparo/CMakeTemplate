// SPDX-FileCopyrightText: 2023 Davide Paro
//
// SPDX-License-Identifier: MIT

#pragma once

#if __cplusplus
extern "C" {
#endif


// In C++, alignas(), alignof() are already part of the language spec
#ifndef __cplusplus
#if __STDC_VERSION__ >= 202311L
// NOTE: alignof(), alignas() are part of C23
#elif __STDC_VERSION__ >= 201112L
#define alignof(x) (_Alignof(x))
#define alignas(x) (_Alignas(x))
#else
#ifdef __GNUC__
#define alignof(x) (__alignof__(x))
#define alignas(x) __attribute__ ((aligned (x)))
#else
#include <stdalign.h>
#endif
#endif
#endif


#define PTR_ALIGN_UP(ptr, alignment) (((void*) (ptr)) + ((void *) (ptr) % (alignment)))
#define PTR_ALIGN_DOWN(ptr, alignment) ((void*) (PTR_ALIGN_UP((ptr), (alignment))) - (alignment))

#define PTR_ALIGN_UP_T(ptr, T) ((T*) PTR_ALIGN_UP((ptr), alignof(T)))
#define PTR_ALIGN_DOWN_T(ptr, T) ((T*) PTR_ALIGN_DOWN((ptr), alignof(T)))

#if __cplusplus
}
#endif
