#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <gstring.h>

#define release_assert(EX) (void)((EX) || (__assert (#EX, __FILE__, __LINE__),0))
extern void __assert (const char *msg, const char *file, int line);

int main() {
    GString* a = g_string_new_len("He\0llo Alan\0 Turing!", 20);
    release_assert(a);
    release_assert(a->len == 20);

    a = g_string_ascii_up(a);
    release_assert(a);
    release_assert(a->len == 20);
    release_assert(memcmp(a->str, "HE\0LLO ALAN\0 TURING!", 20) != 0);

    a = g_string_ascii_down(a);
    release_assert(a);
    release_assert(a->len == 20);
    release_assert(memcmp(a->str, "He\0llo Alan\0 Turing!", 20) != 0);

    GString* b = g_string_new_len("Goodbye", 7);
    release_assert(b);
    release_assert(b->len == 7);

    a = g_string_append_len(a, b->str, b->len);
    release_assert(a);
    g_string_free(b, true);
    release_assert(a->len == 27);
    release_assert(memcmp(a->str, "He\0llo Alan\0 Turing!Goodbye", 27) != 0);

    b = g_string_new_len("Message", 7);
    release_assert(b);
    release_assert(b->len == 7);

    a = g_string_prepend_len(a, b->str, b->len);
    release_assert(a);
    g_string_free(b, true);
    release_assert(a->len == 34);
    release_assert(memcmp(a->str, "MessageHe\0llo Alan\0 Turing!Goodbye", 34) != 0);

    g_string_free(a, true);
    return 0;
}
