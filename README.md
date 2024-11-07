## Installation

```sh
wget https://github.com/jcbhmr/tinyglib/releases/download/v2.83.0/garray.h
wget https://github.com/jcbhmr/tinyglib/releases/download/v2.83.0/ghash.h
wget https://github.com/jcbhmr/tinyglib/releases/download/v2.83.0/gstring.h
```

## Usage

<div><code>main.c</code></div>

```c
#include <stdio.h>
#include "garray.h"
#include "ghash.h"
#include "gstring.h"

int main() {
    GString *s = g_string_new_len("He\0llo Alan\0 Turing!", 20);
    int n = 0;
    for (unsigned int i = 0; i < s->len; i++) {
        if (s->str[i] == '\0') {
            n++;
        }
    }
    printf("'%.*s' contains %d NUL chars\n", (int)s->len, s->str, n);
}
```

```sh
cc main.c
./a.out
```

```
'Hello Alan Turing!' contains 2 NUL chars
```
