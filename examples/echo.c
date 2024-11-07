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

int main(int argc, char *argv[]) {
    GArray* args = g_array_new(false, false, sizeof(GString*));
    g_array_set_clear_func(args, g_string_clear_func);
    for (int i = 0; i < argc; i++) {
        GString* arg = g_string_new(argv[i]);
        args = g_array_append_vals(args, &arg, 1);
    }

    for (unsigned int i = 0; i < args->len; i++) {
        GString* arg = ((GString**)args->data)[i];
        fwrite(arg->str, 1, arg->len, stdout);
        fputs(" ", stdout);
    }
    fputc('\n', stdout);

    g_array_free(args, true);
    return 0;
}
