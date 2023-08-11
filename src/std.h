// SPDX-FileCopyrightText: 2023 Davide Paro
//
// SPDX-License-Identifier: MIT

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <builtins.h>
#include <assert.h>

#if __cplusplus
extern "C" {
#endif

// typeof
#ifndef __cplusplus
#if __STDC_VERSION__ >= 202311L
// NOTE: typeof() are part of C23
#else
#ifdef __GNUC__
#define typeof(x) __typeof__(x)
#endif
#endif
#else
#define typeof(x) decltype(x)
#endif

#ifndef __cplusplus
#ifdef __GNUC__
#define auto __auto_type
#endif
#else
// NOTE: auto is part of C++
#endif

// In C++, alignas(), alignof() are already part of the language spec
#if !defined alignas && !defined alignof
#ifndef __cplusplus
#if __STDC_VERSION__ >= 202311L
// NOTE: alignof(), alignas() are part of C23
#elif __STDC_VERSION__ >= 201112L
#define alignof(x) (_Alignof(x))
#define alignas(x) (_Alignas(x))
#else
#ifdef __GNUC__
#define alignof(x) (__alignof__(x))
#define alignas(x) __attribute__((aligned(x)))
#else
#include <stdalign.h>
#endif
#endif
#endif
#endif

#ifdef MAX
#undef MAX
#endif
#define MAX(a, b)                                                                                  \
    ({                                                                                             \
        auto _a = (a);                                                                             \
        auto _b = (b);                                                                             \
        _a > _b ? _a : _b;                                                                         \
    })

#ifdef MIN
#undef MIN
#endif
#define MIN(a, b)                                                                                  \
    ({                                                                                             \
        auto _a = (a);                                                                             \
        auto _b = (b);                                                                             \
        _a < _b ? _a : _b;                                                                         \
    })

#define SWAP(a, b)                                                                                 \
    ({                                                                                             \
        auto *_a = &(a);                                                                           \
        auto *_b = &(b);                                                                           \
        auto _t = _a;                                                                              \
        *_a = *_b;                                                                                 \
        *_b = _t;                                                                                  \
    })

#ifdef IS_POW2
#undef IS_POW2
#endif
#define IS_POW2(x)                                                                                 \
    ({                                                                                             \
        auto _x = (x);                                                                             \
        (((_x - 1) & _x) == 0);                                                                    \
    })

#define ASSERT_POW2(x) (assert(IS_POW2(x)))
#define ASSERT_ZERO(x) (assert((x) == (typeof(x))0))
#define ASSERT_NZERO(x) (assert((x) != (typeof(x))0))
#define ASSERT_POS(x) (assert((x) > (typeof(x))0))
#define ASSERT_NEG(x) (assert((x) < (typeof(x))0))

#define PTR_ALIGN_UP(ptr, alignment)                                                               \
    ({                                                                                             \
        auto _ptr = (ptr);                                                                         \
        auto _alignment = MAX((size_t)(alignment), 1U);                                            \
        (BUILTIN_IS_CONSTANT(alignment) && IS_POW2(_alignment))                                    \
            ? (typeof(_ptr))((((ptr_t)_ptr + _alignment - 1)) & ~(_alignment - 1))                 \
            : (typeof(_ptr))(((ptr_t)_ptr + (size_t)_alignment - 1) / _alignment * _alignment);    \
    })

#define PTR_ALIGN_DOWN(ptr, alignment)                                                             \
    ({                                                                                             \
        auto _ptr = (ptr);                                                                         \
        auto _alignment = MAX((size_t)(alignment), 1U);                                            \
        (BUILTIN_IS_CONSTANT(alignment) && IS_POW2(_alignment))                                    \
            ? (typeof(_ptr))((ptr_t)_ptr & ~(_alignment - 1))                                      \
            : (typeof(_ptr))(((ptr_t)_ptr / _alignment) * _alignment);                             \
    })

#define PTR_ALIGN_UP_T(ptr) (PTR_ALIGN_UP((ptr), alignof(typeof((ptr)[0]))))
#define PTR_ALIGN_DOWN_T(ptr) (PTR_ALIGN_DOWN((ptr), alignof(typeof((ptr)[0]))))

#define PTR_IS_ALIGNED(ptr, alignment) __ptr_is_aligned(PTR(ptr), alignment)

BUILTIN_ALWAYS_INLINE
static bool __ptr_is_aligned(ptr_t ptr, size_t alignment) {
    return PTR_ALIGN_UP(ptr, alignment) == ptr;
}

BUILTIN_ALWAYS_INLINE
static ptr_t ptr_roundup(ptr_t ptr, size_t alignment) {
    alignment = MAX(1U, alignment);
    return (ptr + alignment - 1) / alignment * alignment;
}

BUILTIN_ALWAYS_INLINE
static ptr_t ptr_roundup_pow2(ptr_t ptr, size_t alignment) {
    alignment = MAX(1U, alignment);
    ASSERT_POW2(alignment);
    return (ptr + alignment - 1) & ~(alignment - 1);
}

BUILTIN_ALWAYS_INLINE
static ptr_t ptr_rounddown(ptr_t ptr, size_t alignment) {
    alignment = MAX(1U, alignment);
    return ptr / alignment * alignment;
}

BUILTIN_ALWAYS_INLINE
static ptr_t ptr_rounddown_pow2(ptr_t ptr, size_t alignment) {
    alignment = MAX(1U, alignment);
    ASSERT_POW2(alignment);
    return ptr & ~(alignment - 1);
}

BUILTIN_ALWAYS_INLINE
static size_t roundup(size_t val, size_t alignment) {
    alignment = MAX(1U, alignment);
    return (val + alignment - 1) / alignment * alignment;
}

BUILTIN_ALWAYS_INLINE
static size_t roundup_pow2(size_t val, size_t alignment) {
    alignment = MAX(1U, alignment);
    ASSERT_POW2(alignment);
    return (val + alignment - 1) & ~(alignment - 1);
}

BUILTIN_ALWAYS_INLINE
static size_t rounddown(size_t val, size_t alignment) {
    alignment = MAX(1U, alignment);
    return val / alignment * alignment;
}

BUILTIN_ALWAYS_INLINE
static size_t rounddown_pow2(size_t val, size_t alignment) {
    alignment = MAX(1U, alignment);
    ASSERT_POW2(alignment);
    return val & ~(alignment - 1);
}

#if __cplusplus
}
#endif
