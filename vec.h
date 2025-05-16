#ifndef VEC_H_DEFINED
#define VEC_H_DEFINED

/*
 *                     __
 *  _   _____  _____  / /_
 * | | / / _ \/ ___/ / __ \
 * | |/ /  __/ /___ / / / /
 * |___/\___/\___(_)_/ /_/
 *
 * vec.h - Lightweight dynamic array implementation using macros in C.
 * Author: OguzhanUmutlu
 * License: MIT
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __vec_fn_name_format
    #define __vec_fn_name_format(name, base, fn_name) vec_##base##_##fn_name
#endif

#define vec_define(type, name, fn_name)                                        \
    typedef struct {                                                           \
        size_t size, capacity;                                                 \
        type *data;                                                            \
    } name;                                                                    \
                                                                               \
    static inline name *__vec_fn_name_format(name, alloc, fn_name)(void) {     \
        return (name *)malloc(sizeof(name));                                   \
    }                                                                          \
                                                                               \
    static inline void __vec_fn_name_format(name, init2, fn_name)(             \
        name * v, size_t reserved) {                                           \
        v->size = 0;                                                           \
        v->capacity = reserved;                                                \
        if (!(v->data = malloc(sizeof(type) * v->capacity))) {                 \
            perror("malloc failed");                                           \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    static inline void __vec_fn_name_format(name, init, fn_name)(name * v) {   \
        __vec_fn_name_format(name, init2, fn_name)(v, 4);                      \
    }                                                                          \
                                                                               \
    static inline void __vec_fn_name_format(name, realloc,                     \
                                            fn_name)(name * v, size_t n) {     \
        if (n == v->capacity)                                                  \
            return;                                                            \
        if (n == 0) {                                                          \
            free(v->data);                                                     \
            v->data = NULL;                                                    \
        } else if (v->data == NULL) {                                          \
            v->data = malloc(sizeof(type) * n);                                \
            if (!v->data) {                                                    \
                perror("malloc failed");                                       \
                exit(EXIT_FAILURE);                                            \
            }                                                                  \
        } else {                                                               \
            type *newData = realloc(v->data, sizeof(type) * n);                \
            if (!newData) {                                                    \
                perror("realloc failed");                                      \
                exit(EXIT_FAILURE);                                            \
            }                                                                  \
            v->data = newData;                                                 \
        }                                                                      \
        v->capacity = n;                                                       \
        if (v->size > n)                                                       \
            v->size = n;                                                       \
    }                                                                          \
                                                                               \
    static inline void __vec_fn_name_format(name, push, fn_name)(name * v,     \
                                                                 type x) {     \
        if (v->size >= v->capacity)                                            \
            __vec_fn_name_format(name, realloc, fn_name)(                      \
                v, v->capacity > 1 ? (v->capacity + (v->capacity >> 1)) : 2);  \
        v->data[v->size++] = x;                                                \
    }                                                                          \
                                                                               \
    static inline type __vec_fn_name_format(name, pop, fn_name)(name * v) {    \
        return v->data[v->size == 0 ? 0 : --v->size];                          \
    }                                                                          \
                                                                               \
    static inline type *__vec_fn_name_format(name, back, fn_name)(name v) {    \
        return v.size == 0 ? NULL : &v.data[v.size - 1];                       \
    }                                                                          \
                                                                               \
    static inline void __vec_fn_name_format(name, clear, fn_name)(name * v) {  \
        v->size = 0;                                                           \
    }                                                                          \
                                                                               \
    static inline bool __vec_fn_name_format(name, empty, fn_name)(name v) {    \
        return v.size == 0;                                                    \
    }                                                                          \
                                                                               \
    static inline type __vec_fn_name_format(name, at, fn_name)(name v,         \
                                                               size_t i) {     \
        if (i < 0 || i >= v.size) {                                            \
            perror("vector index out of bounds");                              \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
        return v.data[i];                                                      \
    }                                                                          \
                                                                               \
    static inline void __vec_fn_name_format(name, set, fn_name)(               \
        name * v, size_t i, type x) {                                          \
        if (i < 0 || i >= v->size) {                                           \
            perror("vector index out of bounds");                              \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
        v->data[i] = x;                                                        \
    }                                                                          \
                                                                               \
    static inline void __vec_fn_name_format(name, resize, fn_name)(            \
        name * v, size_t n, type def_val) {                                    \
        if (n > v->capacity) {                                                 \
            __vec_fn_name_format(name, realloc, fn_name)(v, n);                \
            if (n != 0) {                                                      \
                while (v->size < n) {                                          \
                    v->data[v->size++] = def_val;                              \
                }                                                              \
            }                                                                  \
        }                                                                      \
        v->size = n;                                                           \
    }                                                                          \
                                                                               \
    static inline void __vec_fn_name_format(name, shrink, fn_name)(name * v) { \
        if (v->size != v->capacity)                                            \
            __vec_fn_name_format(name, realloc, fn_name)(v, v->size);          \
    }                                                                          \
                                                                               \
    static inline void __vec_fn_name_format(name, reserve,                     \
                                            fn_name)(name * v, size_t n) {     \
        if (n > v->capacity)                                                   \
            __vec_fn_name_format(name, realloc, fn_name)(v, n);                \
    }                                                                          \
                                                                               \
    static inline void __vec_fn_name_format(name, reverse,                     \
                                            fn_name)(name * v) {               \
        for (size_t i = 0; i < v->size / 2; i++) {                             \
            type tmp = v->data[i];                                             \
            v->data[i] = v->data[v->size - 1 - i];                             \
            v->data[v->size - 1 - i] = tmp;                                    \
        }                                                                      \
    }

#define vec_define_contains(type, name, fn_name)                               \
    static inline bool fn_name(name v, type k) {                               \
        for (size_t i = 0; i < v.size; i++) {                                  \
            if (v.data[i] == k)                                                \
                return true;                                                   \
        }                                                                      \
        return false;                                                          \
    }

#define vec_define_contains_fn(type, name, fn_name, eq_name)                   \
    static inline bool fn_name(name v, type k) {                               \
        for (size_t i = 0; i < v.size; i++) {                                  \
            if (eq_name(v.data[i], k))                                         \
                return true;                                                   \
        }                                                                      \
        return false;                                                          \
    }

#define vec_define_print(type, name, fn_name, print_name)                      \
    static inline void fn_name(name v, size_t indent) {                        \
        if (!v.data) {                                                         \
            printf(#type "[]");                                                \
            return;                                                            \
        }                                                                      \
        printf(#type "[");                                                     \
        if (v.size == 0) {                                                     \
            printf("]");                                                       \
            return;                                                            \
        }                                                                      \
        putchar('\n');                                                         \
        for (size_t i = 0; i < v.size; i++) {                                  \
            ___vec_print_indent(indent);                                       \
            print_name(v.data[i], indent + 2);                                 \
            if (i < v.size - 1)                                                \
                putchar(',');                                                  \
            putchar('\n');                                                     \
        }                                                                      \
        ___vec_print_indent(indent == 0 ? 0 : indent - 1);                     \
        putchar(']');                                                          \
    }

#define vec_define_free(type, name, fn_name, free_fn)                          \
    static inline void fn_name(name *v) {                                      \
        if (!v || !v->data)                                                    \
            return;                                                            \
        for (size_t i = 0; i < v->size; i++) {                                 \
            free_fn(v->data[i]);                                               \
        }                                                                      \
        free(v->data);                                                         \
        v->data = NULL;                                                        \
    }                                                                          \
    static inline void fn_name##_heap(name *v) {                               \
        fn_name(v);                                                            \
        free(v);                                                               \
    }

#define ___vec_print_indent(indent)                                            \
    do {                                                                       \
        for (size_t __i1 = 0; __i1 < (indent) * 2; __i1++)                     \
            putchar(' ');                                                      \
    } while (0)

#endif // VEC_H_DEFINED