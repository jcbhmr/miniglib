#pragma once
// https://github.com/aheck/clib/blob/abd53ca46629a006b7f0e8340cb5fd67d20f9262/src/gstring.h
// MIT License
//
// CHANGES:
// - Removed "#ifdef _CLIB_IMPL" so that the implementations are always present.
// - Added "inline" to all the implementation functions.
// - Use "#pragma once" instead of "#ifndef _<HEADER>_H" guards.

/*
 * GHashTable
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

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define GHASHTABLE_MIN_SLOTS 64
#define GHASHTABLE_MAX_LOAD 0.5

typedef uint32_t (*GHashFunc)(void *key);
typedef bool (*GEqualFunc)(void *a, void *b);
typedef void (*GDestroyNotify)(void *data);
typedef void (*GHFunc) (void *key, void *value, void *user_data);
typedef bool (*GHRFunc) (void *key, void *value, void *user_data);

struct GHashTableSlot {
    void *key;
    void *value;
    bool used : 1;
    bool deleted : 1;
};

typedef struct GHashTable {
    uint32_t num_slots;
    uint32_t num_used;
    uint32_t resize_threshold;
    GHashFunc hash_func;
    GEqualFunc key_equal_func;
    GDestroyNotify key_destroy_func;
    GDestroyNotify value_destroy_func;
    struct GHashTableSlot *slots;
} GHashTable;

uint32_t g_int_hash(void *v);
bool g_int_equal(void *v1, void *v2);
uint32_t g_str_hash(void *v);
bool g_str_equal(void *v1, void *v2);
GHashTable *g_hash_table_new(GHashFunc hash_func, GEqualFunc key_equal_func);
GHashTable *g_hash_table_new_full(GHashFunc hash_func, GEqualFunc key_equal_func, GDestroyNotify key_destroy_func, GDestroyNotify value_destroy_func);
void g_hash_table_insert(GHashTable *hash_table, void *key, void *value);
uint32_t g_hash_table_size(GHashTable *hash_table);
void* g_hash_table_lookup(GHashTable *hash_table, void *key);
void g_hash_table_foreach(GHashTable *hash_table, GHFunc func, void *user_data);
bool g_hash_table_remove(GHashTable *hash_table, void *key);
void g_hash_table_destroy(GHashTable *hash_table);

