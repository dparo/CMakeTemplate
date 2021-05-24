#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <unity.h>

static void test_success(void) {
    TEST_ASSERT_EQUAL(1 + 2, 3);
}

static void test_failure(void) {
    TEST_ASSERT_EQUAL(5 + 5, 100);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_success);
    RUN_TEST(test_failure);
    return UNITY_END();
}

/// Ran before each test
void setUp(void) {}

/// Ran after each test
void tearDown(void) {}
