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

// This macro is used to create a unique function name by concatenating
#define _VCFN(fn_name, op) fn_name##_##op
// This macro determines the indentation multiplier
// Basically if you set this to 2 and use _VCINDENT(3) it will print 3 * 2 = 6
// spaces.
#define _VCINDENT_MULT 2
#define _VCINDENT(indent)                                                      \
    do {                                                                       \
        for (size_t __i1 = 0; __i1 < (indent) * _VCINDENT_MULT; __i1++)        \
            putchar(' ');                                                      \
    } while (0)

#define vec_define(type, name) vec_define2(type, name, name)

#define vec_define2(type, name, fn_name)                                       \
    typedef struct {                                                           \
        size_t size, capacity;                                                 \
        type *data;                                                            \
    } name;                                                                    \
                                                                               \
    static inline name *_VCFN(fn_name, alloc)(void) {                          \
        return (name *)malloc(sizeof(name));                                   \
    }                                                                          \
                                                                               \
    static inline void _VCFN(fn_name, init_reserved)(name * v,                 \
                                                     size_t reserved) {        \
        v->size = 0;                                                           \
        v->capacity = reserved;                                                \
        if (!(v->data = malloc(sizeof(type) * v->capacity))) {                 \
            perror("malloc failed");                                           \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
    }                                                                          \
                                                                               \
    static inline void _VCFN(fn_name, init)(name * v) {                        \
        _VCFN(fn_name, init_reserved)(v, 4);                                   \
    }                                                                          \
                                                                               \
    static inline void _VCFN(fn_name, realloc)(name * v, size_t n) {           \
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
    static inline void _VCFN(fn_name, push)(name * v, type x) {                \
        if (v->size >= v->capacity)                                            \
            _VCFN(fn_name, realloc)(                                           \
                v, v->capacity > 1 ? (v->capacity + (v->capacity >> 1)) : 2);  \
        v->data[v->size++] = x;                                                \
    }                                                                          \
                                                                               \
    static inline type _VCFN(fn_name, pop)(name * v) {                         \
        return v->data[v->size == 0 ? 0 : --v->size];                          \
    }                                                                          \
                                                                               \
    static inline type *_VCFN(fn_name, back)(name v) {                         \
        return v.size == 0 ? NULL : &v.data[v.size - 1];                       \
    }                                                                          \
                                                                               \
    static inline bool _VCFN(fn_name, empty)(name v) {                         \
        return v.size == 0;                                                    \
    }                                                                          \
                                                                               \
    static inline type _VCFN(fn_name, at)(name v, size_t i) {                  \
        if (i < 0 || i >= v.size) {                                            \
            perror("vector index out of bounds");                              \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
                                                                               \
        return v.data[i];                                                      \
    }                                                                          \
                                                                               \
    static inline void _VCFN(fn_name, set)(name * v, size_t i, type x) {       \
        if (i < 0 || i >= v->size) {                                           \
            perror("vector index out of bounds");                              \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
                                                                               \
        v->data[i] = x;                                                        \
    }                                                                          \
                                                                               \
    static inline void _VCFN(fn_name, shrink)(name * v) {                      \
        if (v->size != v->capacity)                                            \
            _VCFN(fn_name, realloc)(v, v->size);                               \
    }                                                                          \
                                                                               \
    static inline void _VCFN(fn_name, reserve)(name * v, size_t n) {           \
        if (n > v->capacity)                                                   \
            _VCFN(fn_name, realloc)(v, n);                                     \
    }                                                                          \
                                                                               \
    static inline void _VCFN(fn_name, reverse)(name * v) {                     \
        for (size_t i = 0; i < v->size / 2; i++) {                             \
            type tmp = v->data[i];                                             \
            v->data[i] = v->data[v->size - 1 - i];                             \
            v->data[v->size - 1 - i] = tmp;                                    \
        }                                                                      \
    }

#define vec_define_contains(type, name, eq_st)                                 \
    vec_define_contains2(type, name, name, eq_st)
#define vec_define_contains2(type, name, fn_name, eq_st)                       \
    static inline bool _VCFN(fn_name, contains)(name v, type b) {              \
        for (size_t i = 0; i < v.size; i++) {                                  \
            type a = v.data[i];                                                \
            if (eq_st)                                                         \
                return true;                                                   \
        }                                                                      \
        return false;                                                          \
    }

#define vec_define_sort(type, name, comp_st)                                   \
    vec_define_sort2(type, name, name, comp_st)
#define vec_define_sort2(type, name, fn_name, comp_st)                         \
    static int _VCFN(fn_name, sort_adapter)(const void *a_ptr,                 \
                                            const void *b_ptr) {               \
        const type a = *(const type *)a_ptr;                                   \
        const type b = *(const type *)b_ptr;                                   \
        return (comp_st);                                                      \
    }                                                                          \
                                                                               \
    static int _VCFN(fn_name, sort_adapter_rev)(const void *a_ptr,             \
                                                const void *b_ptr) {           \
        const type a = *(const type *)a_ptr;                                   \
        const type b = *(const type *)b_ptr;                                   \
        return -(comp_st);                                                     \
    }                                                                          \
                                                                               \
    static inline void _VCFN(fn_name, sort)(name * v) {                        \
        qsort(v->data, v->size, sizeof(type), _VCFN(fn_name, sort_adapter));   \
    }                                                                          \
                                                                               \
    static inline void _VCFN(fn_name, sort_reversed)(name * v) {               \
        qsort(v->data, v->size, sizeof(type),                                  \
              _VCFN(fn_name, sort_adapter_rev));                               \
    }

#define vec_define_print(type, name, print_st)                                 \
    vec_define_print2(type, name, name, print_st, 1)
#define vec_define_print2(type, name, fn_name, print_st, newline)              \
    static inline void _VCFN(fn_name, print_indent)(name v, size_t indent) {   \
        if (!v.data) {                                                         \
            printf(#type "[]");                                                \
            return;                                                            \
        }                                                                      \
        printf(#type "[");                                                     \
        if (v.size == 0) {                                                     \
            printf("]");                                                       \
            return;                                                            \
        }                                                                      \
        if (newline)                                                           \
            putchar('\n');                                                     \
        indent++;                                                              \
        for (size_t i = 0; i < v.size; i++) {                                  \
            _VCINDENT(indent);                                                 \
            type a = v.data[i];                                                \
            print_st;                                                          \
            if (i < v.size - 1)                                                \
                putchar(',');                                                  \
            if (newline)                                                       \
                putchar('\n');                                                 \
        }                                                                      \
        _VCINDENT(indent <= 1 ? 0 : indent - 2);                               \
        putchar(']');                                                          \
    };                                                                         \
                                                                               \
    static inline void _VCFN(fn_name, print)(name v) {                         \
        _VCFN(fn_name, print_indent)(v, 0);                                    \
    }

#define vec_define_free_simple(type, name)                                     \
    static inline void _VCFN(fn_name, clear)(name * v) {                       \
        if (!v->data)                                                          \
            return;                                                            \
        free(v->data);                                                         \
        v->data = NULL;                                                        \
        v->size = 0;                                                           \
        v->capacity = 0;                                                       \
    }                                                                          \
                                                                               \
    static inline void _VCFN(fn_name, resize)(name * v, size_t n,              \
                                              type def_val) {                  \
        if (n > v->capacity) {                                                 \
            _VCFN(fn_name, realloc)(v, n);                                     \
            while (v->size < n) {                                              \
                v->data[v->size++] = def_val;                                  \
            }                                                                  \
        }                                                                      \
        v->size = n;                                                           \
    }

#define vec_define_free(type, name, free_st)                                   \
    vec_define_free2(type, name, name, free_st)
#define vec_define_free2(type, name, fn_name, free_st)                         \
    static inline void _VCFN(fn_name, clear)(name * v) {                       \
        if (!v->data)                                                          \
            return;                                                            \
        for (size_t i = 0; i < v->size; i++) {                                 \
            type a = v->data[i];                                               \
            free_st;                                                           \
        }                                                                      \
        free(v->data);                                                         \
        v->data = NULL;                                                        \
        v->size = 0;                                                           \
        v->capacity = 0;                                                       \
    }                                                                          \
                                                                               \
    static inline void _VCFN(fn_name, resize)(name * v, size_t n,              \
                                              type def_val) {                  \
        if (n > v->capacity) {                                                 \
            for (size_t i = n; i < v->size; i++) {                             \
                type a = v->data[i];                                           \
                free_st;                                                       \
            }                                                                  \
            _VCFN(fn_name, realloc)(v, n);                                     \
            while (v->size < n) {                                              \
                v->data[v->size++] = def_val;                                  \
            }                                                                  \
        }                                                                      \
        v->size = n;                                                           \
    }

#define vec_define_all(type, name, print_st, eq_st, comp_st, free_st)          \
    vec_define_all2(type, name, name, print_st, eq_st, comp_st, free_st)
#define vec_define_all2(type, name, fn_name, print_st, eq_st, comp_st,         \
                        free_st)                                               \
    vec_define2(type, name, fn_name);                                          \
    vec_define_print2(type, name, fn_name, print_st, 1);                       \
    vec_define_contains2(type, name, fn_name, eq_st);                          \
    vec_define_sort2(type, name, fn_name, comp_st);                            \
    vec_define_free2(type, name, fn_name, free_st);

#define vec_define_primitive(type, fmt)                                        \
    vec_define(type, type##s);                                                 \
    vec_define_print(type, type##s, printf(fmt, a));                           \
    vec_define_contains(type, type##s, a == b);                                \
    vec_define_sort(type, type##s, a - b);                                     \
    vec_Define_free(type, type##s);

#endif // VEC_H_DEFINED