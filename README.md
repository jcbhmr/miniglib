# MiniGLib

📄 Just the core GLib types: `GString`, `GArray`, and `GHashTable`

<table align=center><td>

```c
GString *name = g_string_new("Alan Turing");
printf("👋 Hello %.*s!\n", (int) name->len, name->str);
```

</table>

## Installation

```sh
git submodule add https://github.com/jcbhmr/miniglib.git
git -C ./miniglib switch v2.81.0
```

<details><summary>Using CMake</summary>

```cmake
add_subdirectory(miniglib)
target_link_libraries(myapp PRIVATE miniglib::miniglib)
```

</details>

<details><summary>Using the build output with a C compiler directly</summary>

```sh
cmake -D CMAKE_BUILD_TYPE=Release -B ./miniglib/build/ -S ./miniglib/
cc -I ./miniglib/include/ -L ./miniglib/build/ -l miniglib -o ./myapp ./myapp.c
```

</details>

## Usage

After downloading the library and configuring your build system to link against it, you can use the following code snippets to get started.

```c
#include <stdio.h>
#include <miniglib.h>

int main() {
    GString *name1 = g_string_new("Alan Turing");
    GString *name2 = g_string_new("Ada Lovelace");
    printf("%.*s says hello to %.*s\n", (int) name1->len, name1->str, (int) name2->len, name2->str);
    g_string_free(name1, true);
    g_string_free(name2, true);
}
```

```c
#include <stddef.h>
#include <stdio.h>
#include <miniglib.h>

int main() {
    GArray *names = g_array_new(false, false, sizeof(GString *));
    g_array_append_val(names, g_string_new("Alan Turing"));
    g_array_append_val(names, g_string_new("Ada Lovelace"));
    g_array_append_val(names, g_string_new("Grace Hopper"));
    for (size_t i = 0; i < names->len; i++) {
        GString *name = g_array_index(names, GString *, i);
        printf("Name #%d: %.*s\n", (int) i, (int) name->len, name->str);
    }
    for (size_t i = 0; i < names->len; i++) {
        GString *name = g_array_index(names, GString *, i);
        g_string_free(name, true);
    }
    g_array_free(names, true);
}
```

```c
#include <stddef.h>
#include <stdio.h>
#include <miniglib.h>

int main() {
    GHashTable *names = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(ages, g_string_new("Alan"), g_string_new("Turing"));
    g_hash_table_insert(ages, g_string_new("Ada"), g_string_new("Lovelace"));
    g_hash_table_insert(ages, g_string_new("Grace"), g_string_new("Hopper"));
    for (size_t i = 0; i < ages->num_slots; i++) {
        if (!ages->slots[i].used) {
            continue;
        }
        GString *key = ages->slots[i].key;
        GString *value = ages->slots[i].value;
        printf("%.*s: %.*s\n", (int) key->len, key->str, (int) value->len, value->str);
    }
    for (size_t i = 0; i < ages->num_slots; i++) {
        if (!ages->slots[i].used) {
            continue;
        }
        GString *key = ages->slots[i].key;
        GString *value = ages->slots[i].value;
        g_string_free(key, true);
        g_string_free(value, true);
    }
    g_hash_table_destroy(ages);
}
```

## Development


