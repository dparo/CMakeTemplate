#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <unity.h>

static void test_example(void) {
    TEST_ASSERT_EQUAL(1 + 2, 3);
}

static void test_read(void)
{
    FILE *f = fopen("./CMakeLists.txt", "r");
    char buffer[16 * 1024];
    size_t sizeRead = fread(buffer, 1, sizeof(buffer), f);
    TEST_ASSERT_GREATER_OR_EQUAL(64, sizeRead);
    fclose(f);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_example);
    RUN_TEST(test_read);
    return UNITY_END();
}

/// Ran before each test
void setUp(void) {}

/// Ran after each test
void tearDown(void) {}
