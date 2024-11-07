/*!
MIT License

Copyright (c) 2024 Jacob Hummer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef GARRAY_H
#define GARRAY_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>

typedef int (*GCompareFunc)(const void* a, const void* b);
typedef int (*GCompareDataFunc)(const void* a, const void* b, void* user_data);
typedef void (*GDestroyNotify)(void* data);

/**
 * A good C dynamic array struct with methods.
 *
 * - Can be zero-terminated.
 * - Will automatically reallocate.
 * - Can be sorted.
 * - Has a reference counter.
 * - Can run a custom destructor for each element.
 *
 * This struct has the same layout and the same methods with the same types &
 * sizes as [the official GLib project's `GArray`
 * family](https://docs.gtk.org/glib/struct.Array.html). You are able to use
 * these functions on existing GLib `GArray*` objects **as long as they use the
 * same allocator**.
 *
 * This struct also maintains the same source code names for members and
 * parameters to methods. This `GArray*` family should be a drop-in replacement
 * for existing GLib users.
 *
 * This struct should never be used directly as a concrete type. All operations
 * and referencing should be done through pointers. That means using `GArray*
 * my_array` instead of `GArray my_array`.
 *
 * - **`g_array_new()`:** Create a new zero-length array for the given element
 *   type/size.
 * - **`g_array_new_take()`:** Create a new array from an existing `(data, len)`
 *   pair. This takes ownership of the data pointer.
 * - **`g_array_new_take_zero_terminated()`:** Create a new array from an
 *   existing zero-terminated `data` pointer. This takes ownership of the data
 *   pointer.
 * - **`g_array_sized_new()`:** Create a new zero-length array with a
 *   pre-reserved size.
 *
 * Users of this struct should not access the `_*` fields like `_elt_capacity`
 * directly; these are pseudo-private struct members.
 *
 * Make sure you free the array with `g_array_free()` or `g_array_unref()` when
 * you're done with it. This will run the destructor (if set) on all elements in
 * the array.
 *
 * Remember that if an allocation fails the GLib behaviour is to `abort()`. This
 * library has the same behaviour.
 */
typedef struct _GArray {
  char* data;
  unsigned int len;

  unsigned int _elt_capacity;
  unsigned int _elt_size;
  unsigned int _zero_terminated : 1;
  unsigned int _clear : 1;
  atomic_int _ref_count;
  GDestroyNotify _clear_func;
} GArray;

/**
 * Adds `len` elements from `data` to the end of the array. Uses the
 * `element_size` from array creation to compute souce block size from `data +
 * len * array->element_size`. Returns the array. This can reallocate & move the
 * array's data pointer to a new location.
 */
GArray* g_array_append_vals(GArray* array, const void* data, unsigned int len);

/**
 * The array **must be sorted by you, the caller** before calling this function.
 * This function will then use the provided comparator function to find the
 * `target` element in the array.
 *
 * If the element is found, this function returns `true` and sets the
 * `out_match_index` to the index of the item that matched. `out_match_index` is
 * optional; you may provide `NULL` if you don't need it.
 *
 * If the target element is not found then this function returns `false` and
 * does not attempt to set the `out_match_index`.
 *
 * This function does not mutate the array.
 */
bool g_array_binary_search(GArray* array, const void* target, GCompareFunc compare_func, unsigned int* out_match_index);

/**
 * Returns a new array that is a copy of the source array. This will copy all
 * elements and the zero-terminated flag. The new array will have the same
 * element size as the source array.
 */
GArray* g_array_copy(GArray* array);

/**
 * Frees the array and optionally the segment. If `free_segment` is `true`, the
 * array's data segment is also freed. If `free_segment` is `false`, the array's
 * data segment is not freed and the caller is responsible for freeing it.
 *
 * **This function is not thread-safe.** Use `g_array_ref()` and
 * `g_array_unref()` for thread-safe reference counting and automatic freeing.
 */
char* g_array_free(GArray* array, bool free_segment);

/**
 * Returns the size of the element type in bytes. This will return the same
 * value that you passed in when this array was created. You cannot change the
 * element size value after teh array is created.
 */
unsigned int g_array_get_element_size(GArray* array);

GArray* g_array_insert_vals(GArray* array, unsigned int index, const void* data, unsigned int len);
GArray* g_array_new(bool zero_terminated, bool clear, unsigned int element_size);
GArray* g_array_new_take(void* data, size_t len, bool clear, size_t element_size);
GArray* g_array_new_take_zero_terminated(void* data, bool clear, size_t element_size);
GArray* g_array_prepend_vals(GArray* array, const void* data, unsigned int len);
GArray* g_array_ref(GArray* array);
GArray* g_array_remove_index(GArray* array, unsigned int index);
GArray* g_array_remove_index_fast(GArray* array, unsigned int index);
GArray* g_array_remove_range(GArray* array, unsigned int index, unsigned int length);
void g_array_set_clear_func(GArray* array, GDestroyNotify clear_func);
GArray* g_array_set_size(GArray* array, unsigned int length);
GArray* g_array_sized_new(bool zero_terminated, bool clear, unsigned int element_size, unsigned int reserved_size);
void g_array_sort(GArray* array, GCompareFunc compare_func);
void g_array_sort_with_data(GArray* array, GCompareDataFunc compare_func, void* user_data);
void* g_array_steal(GArray* array, size_t* len);
void g_array_unref(GArray* array);

static void _g_array_maybe_expand(GArray* array, unsigned int len);

inline GArray* g_array_append_vals(GArray* array, const void* data, unsigned int len) {
    if (array == NULL) {
        return NULL;
    }
    if (len == 0) {
        return array;
    }
    _g_array_maybe_expand(array, len);
    memcpy(array->data + (array->len * array->_elt_size), data, len * array->_elt_size);
    array->len += len;
}

inline bool g_array_binary_search(GArray* array, const void* target, GCompareFunc compare_func, unsigned int* out_match_index) {
    if (array == NULL) {
        return false;
    }
    if (compare_func == NULL) {
        return false;
    }
    if (array->len > 0) {
        unsigned int left = 0;
        unsigned int right = array->len - 1;
        while (left <= right) {
            unsigned int middle = left + (right - left) / 2;
            int cmp = compare_func(array->data + (middle * array->_elt_size), target);
            if (cmp == 0) {
                if (out_match_index != NULL) {
                    *out_match_index = middle;
                }
                return true;
            } else if (cmp < 0) {
                left = middle + 1;
            } else if (cmp > 0 && middle > 0) {
                right = middle - 1;
            } else {
                break;
            }
        }
    }
    return false;
}

inline GArray* g_array_copy(GArray* array) {
    if (array == NULL) {
        return NULL;
    }
    GArray* new_array = f(array->_zero_terminated, array->_clear, array->_elt_size, array->_elt_capacity);
    new_array->len = array->len;
    if (new_array->len > 0) {
        memcpy(new_array->data, array->data, array->len * array->_elt_size);
    }
    if (array->_zero_terminated) {
        memset(new_array->data + (new_array->len * new_array->_elt_size), 0, new_array->_elt_size);
    }
}

inline char* g_array_free(GArray* array, bool free_segment) {
    if (array == NULL) {
        return NULL;
    }
    char* data;
    if (free_segment) {
        if (array->_clear_func != NULL) {
            for (unsigned int i = 0; i < array->len; i++) {
                array->_clear_func(array->data + (i * array->_elt_size));
            }
        }
        free(array->data);
        data = NULL;
    } else {
        data = array->data;
    }
    if (--array->_ref_count == 0) {
        // free_sized()?
        free(array);
    } else {
        array->data = NULL;
        array->len = 0;
        array->_elt_capacity = 0;
    }
    return data;
}

inline unsigned int g_array_get_element_size(GArray* array) {
    if (array == NULL) {
        return 0;
    }
    return array->_elt_size;
}

inline GArray* g_array_insert_vals(GArray* array, unsigned int index, const void* data, unsigned int len) {
  if (array == NULL) {
    return NULL;
  }
  if (len == 0) {
    return array;
  }
  if (index >= array->len) {
    _g_array_maybe_expand(array, index - array->len + len);
    return g_array_append_vals(g_array_set_size(array, index), data, len);
  }
  _g_array_maybe_expand(array, len);
  memmove(array->data + ((index + len) * array->_elt_size), array->data + (index * array->_elt_size), (array->len - index) * array->_elt_size);
  memcpy(array->data + (index * array->_elt_size), data, len * array->_elt_size);
  array->len += len;
  if (array->_zero_terminated) {
    memset(array->data + (array->len * array->_elt_size), 0, array->_elt_size);
  }
  return array;
}

inline GArray* g_array_new(bool zero_terminated, bool clear, unsigned int element_size) {
    if (elt_size == 0) {
        return NULL;
    }
    return f(zero_terminated, clear, element_size, 0);
}

inline GArray* g_array_new_take(void* data, size_t len, bool clear, size_t element_size) {
    if (data == NULL) {
        return NULL;
    }
    if (len == 0) {
        return NULL;
    }
    GArray* array = f(false, clear, element_size, 0);
    array->data = data;
    array->len = len;
    array->_elt_capacity = len;
    return array;
}

GArray* g_array_new_take_zero_terminated(void* data, bool clear, size_t element_size);

GArray* g_array_prepend_vals(GArray* array, const void* data, unsigned int len);

GArray* g_array_ref(GArray* array);

GArray* g_array_remove_index(GArray* array, unsigned int index);

GArray* g_array_remove_index_fast(GArray* array, unsigned int index);

GArray* g_array_remove_range(GArray* array, unsigned int index, unsigned int length);

void g_array_set_clear_func(GArray* array, GDestroyNotify clear_func);

GArray* g_array_set_size(GArray* array, unsigned int length) {
  if (array == NULL) {
    return NULL;
  }
  if (length > array->len) {
    _g_array_maybe_expand(array, length - array->len);
    if (array->_clear) {
      memset(array->data + (array->len * array->_elt_size), 0, (length - array->len) * array->_elt_size);
    }
  } else if (length < array->len) {
    g_array_remove_range(array, length, array->len - length);
  }
  array->len = length;
  if (array->_zero_terminated) {
    memset(array->data + (array->len * array->_elt_size), 0, array->_elt_size);
  }
  return array;
}

GArray* g_array_sized_new(bool zero_terminated, bool clear, unsigned int element_size, unsigned int reserved_size);

void g_array_sort(GArray* array, GCompareFunc compare_func);

void g_array_sort_with_data(GArray* array, GCompareDataFunc compare_func, void* user_data);

void* g_array_steal(GArray* array, size_t* len);

void g_array_unref(GArray* array);

static inline void _g_array_maybe_expand(GArray* array, unsigned int len) {
    // - Number of bytes must fit into size_t / 2
    // - Number of elements must fit into unsigned int
    // - Zero terminated arrays must leave space for the terminator
    unsigned int max_len;
    // min(a, b)
    unsigned int max_len_candidate_a = (SIZE_MAX / 2) / array->_elt_size;
    unsigned int max_len_candidate_b = UINT_MAX;
    if (max_len_candidate_a < max_len_candidate_b) {
        max_len = max_len_candidate_a - (array->_zero_terminated ? 1 : 0);
    } else {
        max_len = max_len_candidate_b - (array->_zero_terminated ? 1 : 0);
    }
    // Detect overflow.
    if ((max_len - array->len) < len) {
        fprintf(stderr, "adding %u to array would overflow\n", len);
        abort();
    }

    unsigned int want_len = array->len + len + (array->_zero_terminated ? 1 : 0);
    if (want_len > array->_elt_capacity) {
        size_t want_alloc = 1;
        size_t want_alloc_max = array->_elt_size * want_len;
        while (want_alloc < want_alloc_max) {
            want_alloc <<= 1;
        }

        if (want_alloc <= array->_elt_size * want_len) {
            fprintf(stderr, "assertion failed: want_alloc >= array->_elt_size * want_len\n");
            abort();
        }
        array->data = realloc(array->data, want_alloc);
        // min(a, b)
        unsigned int new_capacity_candidate_a = want_alloc / array->_elt_size;
        unsigned int new_capacity_candidate_b = UINT_MAX;
        if (new_capacity_candidate_a < new_capacity_candidate_b) {
            array->_elt_capacity = new_capacity_candidate_a;
        } else {
            array->_elt_capacity = new_capacity_candidate_b;
        }
    }
}

#endif // GARRAY_H