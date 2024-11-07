/**
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <gstring.h>
#include <garray.h>

#define release_assert(EX) (void)((EX) || (__assert (#EX, __FILE__, __LINE__),0))
extern void __assert (const char *msg, const char *file, int line);

void g_string_clear_func(void* s) {
    g_string_free(*((GString**)s), true);
}

typedef enum {
    FS_ENTRY_DIRECTORY,
    FS_ENTRY_FILE,
} fs_entry_tag;
typedef struct {
    fs_entry_tag tag;
    union {
        struct {
            GString* name;
            GArray* children;
        } directory;
        struct {
            GString* name;
            GString* contents;
        } file;
    };
} fs_entry;

void fs_entry_free(fs_entry* entry) {
    release_assert(entry);
    release_assert(entry->tag == FS_ENTRY_DIRECTORY || entry->tag == FS_ENTRY_FILE);
    if (entry->tag == FS_ENTRY_DIRECTORY) {
        g_string_free(entry->directory.name, true);
        g_array_free(entry->directory.children, true);
    } else {
        g_string_free(entry->file.name, true);
        g_string_free(entry->file.contents, true);
    }
}

int main(int argc, char* argv[]) {
    GArray* args = g_array_new(false, false, sizeof(GString*));
    g_array_set_clear_func(args, g_string_clear_func);
    for (int i = 0; i < argc; i++) {
        GString* arg = g_string_new(argv[i]);
        release_assert(arg->len <= INT_MAX);
        args = g_array_append_vals(args, &arg, 1);
    }

    if (args->len == 2 && ((GString**)args->data)[1]->len == 6 && memcmp(((GString**)args->data)[1]->str, "--help", 6) == 0) {
        printf("Usage: %.*s [DIRECTORY]\n", ((GString**)args->data)[0]->len, ((GString**)args->data)[0]->str);
        g_array_free(args, true);
        return 0;
    }
}
