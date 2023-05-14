// SPDX-FileCopyrightText: 2023 Davide Paro
//
// SPDX-License-Identifier: MIT

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <greatest.h>

#include "sum.h"
#include <string.h>

TEST example(void) {
    ASSERT_EQ(1 + 2, 3);
    PASS();
}

TEST calling_fread(void) {
    FILE *f = fopen("./CMakeLists.txt", "r");
    char buffer[16 * 1024];
    size_t sizeRead = fread(buffer, 1, sizeof(buffer), f);
    ASSERT_GTE(sizeRead, 64);
    fclose(f);
    PASS();
}

TEST calling_calloc_0_0(void) {
    char *p = calloc(0, 0);
    ASSERT(p);
    free(p);
    PASS();
}

TEST calling_malloc_0(void) {
    char *p = malloc(0);
    ASSERT(p);
    free(p);
    PASS();
}

TEST calling_sum(void) {
    for (int32_t i = -10; i < 10; i++) {
        for (int32_t j = -10; j < 10; j++) {
            ASSERT_EQ(i + j, sum(i, j));
        }
    }
    PASS();
}

/* Add all the definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN(); /* command-line arguments, initialization. */

    /* If tests are run outside of a suite, a default suite is used. */
    RUN_TEST(example);
    RUN_TEST(calling_fread);
    RUN_TEST(calling_calloc_0_0);
    RUN_TEST(calling_malloc_0);
    RUN_TEST(calling_sum);

    GREATEST_MAIN_END(); /* display results */
}
