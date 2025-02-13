# MiniGLib

📄 Just the core GLib types: `GString`, `GArray`, and `GHashTable`

<table align=center><td>

```c
GString *name = g_string_new("Alan Turing");
printf("👋 Hello %.*s!\n", (int) name->len, name->str);
```

</table>

## Installation

![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=Git&logoColor=FFFFFF)

TODO: Publish to a library repository or something

```sh
git submodule add https://github.com/jcbhmr/miniglib.git
git -C ./miniglib switch v1.0.0
```

```sh
cc -std=c23 -I ./miniglib/include/ -o ./build/hello-world ./miniglib/src/*.c ./src/*.c
```

## Usage

![C](https://img.shields.io/badge/C-222222?style=for-the-badge&logo=C&logoColor=A8B9CC)

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

## Development

![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=CMake&logoColor=FFFFFF)
![C](https://img.shields.io/badge/C-222222?style=for-the-badge&logo=C&logoColor=A8B9CC)

TODO: Write this section
