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
#include <string.h>

typedef struct html_attrs {
    char *class;
    char *style;
} html_attrs_t;

void begin_div(const html_attrs_t *attrs) {
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
//////////////////////////

#define HTML_ATTRIB_KEY_MAX_SIZE 32
#define HTML_MAX_NUM_ATTRS 64
#define HTML_ATTR_BUF_MAX_SIZE (16 * 1024)

typedef struct HtmlElem {
    char tag[32];
    char *text;

    struct {
        uint32_t num_keys;
        uint16_t val_buf_offsets[HTML_MAX_NUM_ATTRS + 1];
        char keys[HTML_ATTRIB_KEY_MAX_SIZE][HTML_MAX_NUM_ATTRS];
        char val_buf[HTML_ATTR_BUF_MAX_SIZE];
    } attrs;
} HtmlElem;

typedef struct HtmlTree {
    HtmlElem elem;
    int32_t num_childs;
    struct HtmlElem *childs[1024];
} HtmlTree;

typedef struct HtmlDoc {
    // <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
    // "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
    char *doctype;
    HtmlElem *root;
} HtmlDoc;

void html_push_attr(HtmlElem *elem, const char *key, const char *value) {
    // Check boundaries for key
    if (elem->attrs.num_keys >= HTML_MAX_NUM_ATTRS || strlen(key) >= HTML_ATTRIB_KEY_MAX_SIZE) {
        // TODO
        return;
    }

    size_t len = strlen(value);
    uint16_t curr_offset = elem->attrs.val_buf_offsets[elem->attrs.num_keys];
    uint16_t new_offset = curr_offset + (uint16_t)len;

    // Check boundaries for values buffer

    if (new_offset < HTML_ATTRIB_KEY_MAX_SIZE) {
        // TODO
        return;
    }

    // Copy key
    strcpy(elem->attrs.keys[elem->attrs.num_keys], key);
    // Copy value into the buffer
    elem->attrs.val_buf_offsets[elem->attrs.num_keys + 1] = new_offset;
    strcpy(&elem->attrs.val_buf[new_offset], value);
    // Update number of keys
    ++elem->attrs.num_keys;
}

#if __cplusplus
}
#endif
