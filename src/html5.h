// SPDX-FileCopyrightText: 2023 Davide Paro
//
// SPDX-License-Identifier: MIT

#pragma once

//
// WORK in progress.
//

#if __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

typedef struct html_attrs {
    char *class;
    char *style;
} html_attrs_t;

void begin_div(html_attrs_t *attrs) {
    printf("<div ");
    if (attrs) {
        if (attrs->class) {
            printf("class=\"%s\"", attrs->class);
        }
        if (attrs->style) {
            printf("style=\"%s\"", attrs->style);
        }
    }
    printf(">");
}

void end_div() { printf("</div>\n"); }

int end_conditional() {
    printf("END conditional\n");
    return 0;
}

#define HTML_BLOCK(attrs, beg, end)                                                                \
    { beg(&(html_attrs_t)attrs); }                                                                 \
    for (int32_t _block_inner_cnt = 0; !_block_inner_cnt; _block_inner_cnt = 1, end())

#define DIV(attrs) HTML_BLOCK(attrs, begin_div, end_div)

static inline void example() {
    DIV({.class = "foo"}) {
        DIV({}) { printf("Hello world\n"); }
    }
}

#if __cplusplus
}
#endif
