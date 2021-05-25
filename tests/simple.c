#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <unity.h>

#include "sum.h"
#include <string.h>

static void test_example(void) {
    TEST_ASSERT_EQUAL(1 + 2, 3);
}

static void test_read(void) {
    FILE* f = fopen("./CMakeLists.txt", "r");
    char buffer[16 * 1024];
    size_t sizeRead = fread(buffer, 1, sizeof(buffer), f);
    TEST_ASSERT_GREATER_OR_EQUAL(64, sizeRead);
    fclose(f);
}

static void test_sum(void) {
    for (int32_t i = -10; i < 10; i++) {
        for (int32_t j = -10; j < 10; j++) {
            TEST_ASSERT_EQUAL(sum(i, j), i + j);
        }
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_example);
    RUN_TEST(test_read);
    RUN_TEST(test_sum);
    return UNITY_END();
}

/// Ran before each test
void setUp(void) {}

/// Ran after each test
void tearDown(void) {}
