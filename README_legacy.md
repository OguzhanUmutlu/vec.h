# ⚠️ Legacy Version – `vec_legacy.h`

> This is the **legacy** version of the `vec` dynamic array library. It uses **pure preprocessor macros** for all functionality, which can lead to less clarity, harder debugging, and limited type safety.

We now recommend using the updated version, which uses **macros to generate actual functions**. This improves readability, debugging, and maintainability — while keeping the API minimal and efficient.

👉 Check out the **updated version** here:

* 📄 [README.md (Current)](./README.md)
* 📂 [vec.h (Current)](./vec.h)

---

## vec.h

A lightweight, macro-based dynamic array implementation for C (C11+).
Supports both **value-based** and **pointer-based** styles with a simple, consistent interface.

## ✨ Features

* Header-only, no dependencies
* Value (`vec_*`) and pointer (`vec_*_p`) interface styles
* Automatic resizing and memory management
* Type-safe via `_Static_assert` (Only for C11+)
* Utility functions for resizing, shrinking, reserving, clearing, and printing
* Custom deallocators supported (`vec_free2`, etc.)

---

## 🚀 Getting Started

Include `vec_legacy.h` in your project:

```c
#include "vec_legacy.h"
```

### Define a vector

```c
vec(int) my_vec;
vec_init(int, my_vec);
```

### Or use pointer style

```c
vec(int)* my_vec = vec_alloc(int);
vec_init_p(int, my_vec);
```

---

## 🧰 Usage Examples

### Push/Pop

```c
vec_push(int, my_vec, 42);
int last = vec_pop(my_vec);
```

### Access

```c
vec_at(my_vec, 0);     // Safe access with bounds check
vec_back(my_vec);      // Last element
vec_set(my_vec, 0, 99);
```

### Resize / Reserve

```c
vec_resize(int, my_vec, 10, 0);  // Resize to 10 with default value 0
vec_reserve(int, my_vec, 100);  // Reserve space for 100 elements
```

### Clear / Shrink

```c
vec_clear(my_vec);      // Set size to 0
vec_shrink(int, my_vec); // Shrink capacity to fit size
```

---

## 🧼 Cleanup

```c
vec_free(my_vec); // For value-style
vec_free_ap(my_vec); // For pointer-style (frees both data and vector)
```

If your vector contains heap-allocated elements:

```c
vec_free2(my_vec, free); // Frees each element and the data array
```

---

## 🖨 Pretty Print

Provide a custom print function and indent level:

```c
void print_int(int val, int indent) {
    for (int i = 0; i < indent; i++) putchar(' ');
    printf("%d", val);
}

vec_print(int, print_int, my_vec, 1);
```

---

## 🧪 Requirements

* Standard C library (`stdlib.h`, `stdio.h`)

---

## 📄 License

MIT License
© [OguzhanUmutlu](https://github.com/OguzhanUmutlu)
