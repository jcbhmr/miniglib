#pragma once
// https://github.com/aheck/clib/blob/abd53ca46629a006b7f0e8340cb5fd67d20f9262/src/gstring.h
// MIT License
//
// CHANGES:
// - Removed "#ifdef _CLIB_IMPL" so that the implementations are always present.
// - Added "inline" to all the implementation functions.
// - Use "#pragma once" instead of "#ifndef _<HEADER>_H" guards.

/*
 * GString
 *
 * Copyright (c) 2022 Andreas Heck <aheck@gmx.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#define GSTRING_MIN_BUF_SIZE 32

#define TRUE  true
#define FALSE false

typedef struct GString {
    char *str;
    size_t len;
    size_t allocated_len;
} GString;

GString* g_string_new(const char *init);
GString* g_string_new_len(const char *init, size_t len);
GString* g_string_sized_new(ptrdiff_t dfl_size);
GString* g_string_assign(GString *string, const char *rval);
GString* g_string_append(GString *string, const char *val);
GString* g_string_append_c(GString *string, char c);
GString* g_string_append_len(GString *string, const char *val, ptrdiff_t len);
GString* g_string_prepend(GString *string, const char *val);
GString* g_string_prepend_c(GString *string, char c);
GString* g_string_prepend_len(GString *string, const char *val, ptrdiff_t len);
GString* g_string_insert(GString *string, ptrdiff_t pos, const char *val);
GString* g_string_insert_c(GString *string, ptrdiff_t pos, char c);
GString* g_string_insert_len(GString *string, ptrdiff_t pos, const char *val, ptrdiff_t len);
GString* g_string_overwrite(GString *string, size_t pos, const char *val);
GString* g_string_overwrite_len(GString *string, size_t pos, const char *val, ptrdiff_t len);
unsigned int g_string_replace(GString *string, const char *find, const char *replace, unsigned int limit);
GString* g_string_erase(GString *string, ptrdiff_t pos, ptrdiff_t len);
GString* g_string_truncate(GString *string, size_t len);
void g_string_vprintf(GString *string, const char *format, va_list args);
void g_string_append_vprintf(GString *string, const char *format, va_list args);
void g_string_printf(GString *string, const char *format, ...);
void g_string_append_printf(GString *string, const char *format, ...);
bool g_string_equal(GString *v, GString *v2);
char* g_string_free(GString *string, bool free_segment);

