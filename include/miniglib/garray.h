#pragma once
// https://github.com/aheck/clib/blob/abd53ca46629a006b7f0e8340cb5fd67d20f9262/src/garray.h
// MIT License
//
// CHANGES:
// - Removed "#ifdef _CLIB_IMPL" so that the implementations are always present.
// - Added "inline" to all the implementation functions.
// - Use "#pragma once" instead of "#ifndef _<HEADER>_H" guards.

/*
 * GArray
 *
 * Copyright (c) 2023 Andreas Heck <aheck@gmx.de>
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
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Needed for qsort_s
#if (defined _WIN32 || defined _WIN64 || defined __WINDOWS__)
#include <search.h>
#endif

// We would need to define _GNU_SOURCE for stdlib.h to declare qsort_r. Since we
// are header-only we better declare it ourselves to make sure we don't define
// _GNU_SOURCE when we shouldn't
#ifdef __linux__
void qsort_r(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, void *), void *arg);
#endif

typedef int(*GCompareFunc) (const void *a, const void *b);
typedef int(*GCompareDataFunc) (const void *a, const void *b, void *user_data);
typedef void (*GDestroyNotify)(void *data);

typedef struct GArray {
    char *data;
    unsigned int len;
    unsigned int _allocated_elements;
    bool _zero_terminated;
    bool _clear;
    unsigned int _element_size;
    GDestroyNotify _clear_func;
} GArray;

GArray* g_array_new(bool zero_terminated, bool clear, unsigned int element_size);
void* g_array_steal(GArray *array, size_t *len);
GArray* g_array_sized_new(bool zero_terminated, bool clear, unsigned int element_size, unsigned int reserved_size);
GArray* g_array_copy(GArray *array);
unsigned int g_array_get_element_size(GArray *array);
#define g_array_append_val(a, v) g_array_append_vals(a, &v, 1);
GArray* g_array_append_vals (GArray *array, const void *data, unsigned int len);
#define g_array_prepend_val(a, v) g_array_prepend_vals(a, &v, 1);
GArray* g_array_prepend_vals(GArray *array, const void *data, unsigned int len);
#define g_array_insert_val(a, i, v) g_array_insert_vals(a, i, &v, 1);
GArray* g_array_insert_vals (GArray *array, unsigned int index, const void *data, unsigned int len);
GArray* g_array_remove_index(GArray *array, unsigned int index);
GArray* g_array_remove_index_fast(GArray *array, unsigned int index);
GArray* g_array_remove_range(GArray *array, unsigned int index, unsigned int length);
void g_array_sort(GArray *array, GCompareFunc compare_func);
void g_array_sort_with_data(GArray *array, GCompareDataFunc compare_func, void *user_data);
bool g_array_binary_search(GArray *array, const void *target, GCompareFunc compare_func, unsigned int *out_match_index);
#define g_array_index(a, t, i) (t) a->data[i * a->_element_size]
GArray* g_array_set_size(GArray *array, unsigned int length);
void g_array_set_clear_func(GArray *array, GDestroyNotify clear_func);

char* g_array_free(GArray *array, bool free_segment);
