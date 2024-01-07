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
#include "std.h"

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

/////////////////////////////////////////////////
/////////////////////////////////////////////////

#define HTML_RENDERER_MAX_DEPTH 128
#define HTML_RENDERER_MAX_TAG_LEN 63
typedef struct HtmlRenderer {
    FILE *fstream;
    int32_t depth;
    char stack[HTML_RENDERER_MAX_DEPTH][HTML_RENDERER_MAX_TAG_LEN + 1];
} HtmlRenderer;

typedef struct HtmlAttrib {
    char *key;
    char *value;
} HtmlAttrib;

static void render_html_begin(HtmlRenderer *const r, const char *tag, size_t num_attribs,
                              const HtmlAttrib attribs[]) {
    if (r->depth >= HTML_RENDERER_MAX_DEPTH || strlen(tag) >= HTML_RENDERER_MAX_TAG_LEN) {
        return;
    }

    strncpy(r->stack[r->depth], tag, HTML_RENDERER_MAX_TAG_LEN + 1);
    ++r->depth;

    // TODO: Escaping
    fprintf(r->fstream, "<%s ", tag);

    for (size_t i = 0; i < num_attribs /* attribs[i].key */; i++) {
        char *key = attribs[i].key;
        char *value = attribs[i].value;

        if (key && value) {
            // TODO: Escaping
            fprintf(r->fstream, "%s=\"%s\" ", key, value);
        }
    }

    fprintf(r->fstream, ">");
}

static void render_html_end(HtmlRenderer *const r) {
    if (r->depth <= 0) {
        return;
    }

    --r->depth;

    // TODO: Escaping
    fprintf(r->fstream, "</%s>", r->stack[r->depth]);
}

#define HTML_ELEM(r, tag, ...)                                                                     \
    {                                                                                              \
        render_html_begin(r, tag, ARRAY_LEN(((HtmlAttrib[]){__VA_ARGS__})),                        \
                          (HtmlAttrib[]){__VA_ARGS__, {NULL, NULL}});                              \
    }                                                                                              \
    for (int _block_inner_cnt = 0; !_block_inner_cnt; _block_inner_cnt = 1, render_html_end(r))

#define DIV(r, ...) HTML_ELEM(r, "div", __VA_ARGS__)

static int test_html_div_render() {
    HtmlRenderer r = {0};
    r.fstream = stdout;

    DIV(&r, {"id", "1"}, {"foo", "bar"}) {
        DIV(&r, {"id", "2"}, {"foo", "bar"}) {
            DIV(&r, {"id", "3"}, {"foo", "bar"}) {}
        }
        DIV(&r, {"id", "4"}, {"foo", "bar"}) {}
    }

    printf("\n");

    return 0;
}

#if __cplusplus
}
#endif
