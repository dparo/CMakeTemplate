// SPDX-FileCopyrightText: 2023 Davide Paro
//
// SPDX-License-Identifier: MIT

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unity.h>

#include "sum.h"
#include <string.h>
#include "std.h"

void setUp(void) { /* This is run before EACH TEST */
}

void tearDown(void) {}

static void test_ptr_is_aligned(void) {
    TEST_ASSERT_TRUE(PTR_IS_ALIGNED(NULL, 1));
    TEST_ASSERT_TRUE(PTR_IS_ALIGNED(NULL, 2));
    TEST_ASSERT_TRUE(PTR_IS_ALIGNED(NULL, 3));
    TEST_ASSERT_TRUE(PTR_IS_ALIGNED(NULL, 4));

    TEST_ASSERT_TRUE(PTR_IS_ALIGNED(1, 1));
    TEST_ASSERT_FALSE(PTR_IS_ALIGNED(1, 2));

    TEST_ASSERT_TRUE(PTR_IS_ALIGNED(4, 1));
    TEST_ASSERT_TRUE(PTR_IS_ALIGNED(4, 2));
    TEST_ASSERT_FALSE(PTR_IS_ALIGNED(4, 3));
    TEST_ASSERT_TRUE(PTR_IS_ALIGNED(4, 4));

    TEST_ASSERT_TRUE(PTR_IS_ALIGNED(0, 128));
    TEST_ASSERT_FALSE(PTR_IS_ALIGNED(1, 128));
    TEST_ASSERT_FALSE(PTR_IS_ALIGNED(2, 128));
    TEST_ASSERT_FALSE(PTR_IS_ALIGNED(4, 128));
    TEST_ASSERT_FALSE(PTR_IS_ALIGNED(64, 128));
    TEST_ASSERT_TRUE(PTR_IS_ALIGNED(128, 128));
    TEST_ASSERT_TRUE(PTR_IS_ALIGNED(256, 128));
    TEST_ASSERT_TRUE(PTR_IS_ALIGNED(512, 128));
}

static void test_ptr_align_up(void) {
    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_UP(0, 512));
    TEST_ASSERT_EQUAL_PTR(512, PTR_ALIGN_UP(1, 512));
    TEST_ASSERT_EQUAL_PTR(512, PTR_ALIGN_UP(2, 512));
    TEST_ASSERT_EQUAL_PTR(512, PTR_ALIGN_UP(511, 512));
    TEST_ASSERT_EQUAL_PTR(512, PTR_ALIGN_UP(512, 512));
    TEST_ASSERT_EQUAL_PTR(1024, PTR_ALIGN_UP(513, 512));

    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_UP(0, 3));
    TEST_ASSERT_EQUAL_PTR(3, PTR_ALIGN_UP(1, 3));
    TEST_ASSERT_EQUAL_PTR(3, PTR_ALIGN_UP(3, 3));
    TEST_ASSERT_EQUAL_PTR(6, PTR_ALIGN_UP(4, 3));

    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_UP_T((uint64_t *)0));
    TEST_ASSERT_EQUAL_PTR(8, PTR_ALIGN_UP_T((uint64_t *)1));
    TEST_ASSERT_EQUAL_PTR(8, PTR_ALIGN_UP_T((uint64_t *)2));
    TEST_ASSERT_EQUAL_PTR(8, PTR_ALIGN_UP_T((uint64_t *)4));
    TEST_ASSERT_EQUAL_PTR(8, PTR_ALIGN_UP_T((uint64_t *)7));
    TEST_ASSERT_EQUAL_PTR(8, PTR_ALIGN_UP_T((uint64_t *)8));
    TEST_ASSERT_EQUAL_PTR(16, PTR_ALIGN_UP_T((uint64_t *)9));
}

static void test_ptr_align_down(void) {
    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_DOWN(0, 512));
    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_DOWN(1, 512));
    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_DOWN(2, 512));
    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_DOWN(511, 512));
    TEST_ASSERT_EQUAL_PTR(512, PTR_ALIGN_DOWN(512, 512));
    TEST_ASSERT_EQUAL_PTR(512, PTR_ALIGN_DOWN(513, 512));

    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_DOWN(0, 3));
    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_DOWN(1, 3));
    TEST_ASSERT_EQUAL_PTR(3, PTR_ALIGN_DOWN(3, 3));
    TEST_ASSERT_EQUAL_PTR(3, PTR_ALIGN_DOWN(4, 3));

    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_DOWN_T((uint64_t *)0));
    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_DOWN_T((uint64_t *)1));
    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_DOWN_T((uint64_t *)2));
    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_DOWN_T((uint64_t *)4));
    TEST_ASSERT_EQUAL_PTR(0, PTR_ALIGN_DOWN_T((uint64_t *)7));
    TEST_ASSERT_EQUAL_PTR(8, PTR_ALIGN_DOWN_T((uint64_t *)8));
    TEST_ASSERT_EQUAL_PTR(8, PTR_ALIGN_DOWN_T((uint64_t *)9));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ptr_is_aligned);
    RUN_TEST(test_ptr_align_up);
    RUN_TEST(test_ptr_align_down);
    return UNITY_END();
}
