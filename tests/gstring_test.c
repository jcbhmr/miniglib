#include <stdio.h>
#include <stdbool.h>
#include <miniglib.h>

int gstring_test(int argc, char** argv) {
    GString *name = g_string_new("Alan Turing");
    printf("👋 Hello %.*s!\n", (int) name->len, name->str);
    g_string_free(name, true);
    return 0;
}
