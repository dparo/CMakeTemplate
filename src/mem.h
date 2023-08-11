// SPDX-FileCopyrightText: 2023 Davide Paro
//
// SPDX-License-Identifier: MIT

#pragma once

#if __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef struct MAllocatorVTable {
    void *(*alloc)(struct MAllocatorVTable *self, size_t size);
    void *(*realloc)(struct MAllocatorVTable *self, void *prev, size_t *new_size);
    void *(*realloc_sized)(struct MAllocatorVTable *self, void *prev, size_t *prev_size,
                           size_t *new_size);
    void (*free)(struct MAllocatorVTable *self, void *ptr);
    void (*free_sized)(struct MAllocatorVTable *self, void *ptr, size_t size);
    void (*clear)(struct MAllocatorVTable *self);
} MAllocatorVTable;

// TODO(d.paro): Provide alignment parames:
//       Take inspiration from: https://github.com/ziglang/zig/blob/master/lib/std/mem/Allocator.zig
#define M_ALLOC(allocator, size) (allocator)->alloc((allocator), (size))
#define M_ALLOC_ARRAY(allocator, T, nmemb)                                                         \
    ((T *)((allocator)->alloc((allocator), sizeof(T) * (nmemb))))
#define M_ALLOC_T(allocator, T) M_ALLOC_ARRAY((allocator), T, 1)

#define M_REALLOC(allocator, ptr, size) (allocator)->realloc((allocator), (ptr), (size))
#define M_REALLOC_ARRAY(allocator, ptr, T, nmemb)                                                  \
    ((T *)((allocator)->realloc((allocator), ptr, sizeof(T) * (nmemb))))
#define M_REALLOC_T(allocator, ptr, T) M_REALLOC_ARRAY((allocator), ptr, T, 1)

#define M_REALLOC_SIZED(allocator, ptr, prev_size, new_size)                                       \
    (allocator)->realloc_sized((allocator), (ptr), (prev_size), (new_size))
#define M_REALLOC_SIZED_ARRAY(allocator, ptr, prev_size, T, nmemb)                                 \
    ((T *)((allocator)->realloc_sized((allocator), (ptr), (prev_size), sizeof(T) * (nmemb))))
#define M_REALLOC_SIZED_T(allocator, ptr, prev_size, T)                                            \
    M_REALLOC_ARRAY((allocator), (ptr), (prev_size), T, 1)

#define M_FREE_SIZED(allocator, ptr, size) (allocator)->free_sized((allocator), (ptr), (size))
#define M_FREE(allocator, ptr, size) (allocator)->free((allocator), (ptr))

#define M_CLEAR(allocator, ptr, size) (allocator)->clear((allocator))

#if __cplusplus
}
#endif
