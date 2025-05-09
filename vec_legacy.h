#ifndef VEC_H_LEGACY_DEFINED
#define VEC_H_LEGACY_DEFINED

/*
 *                     __
 *  _   _____  _____  / /_
 * | | / / _ \/ ___/ / __ \
 * | |/ /  __/ /___ / / / /
 * |___/\___/\___(_)_/ /_/
 *
 * vec_legacy.h - Lightweight dynamic array implementation using macros in C.
 * Supports both value (`vec_*`) and pointer (`vec_*_p`) access styles.
 * Author: OguzhanUmutlu
 * License: MIT
 */

#include <stdio.h>
#include <stdlib.h>

#define vec(type)                                                              \
    struct {                                                                   \
        int size, capacity;                                                    \
        type *data;                                                            \
    }
#define vec_alloc(type) ((vec(type) *)malloc(sizeof(vec(type))))
#define vec_init(type, v) vec_init2(type, v, 4)
#define vec_init2(type, v, reserved)                                           \
    do {                                                                       \
        __vec_type_assert(type, v);                                            \
        (v).size = 0;                                                          \
        (v).capacity = (reserved);                                             \
        if (!((v).data = malloc(sizeof(type) * (v).capacity))) {               \
            perror("malloc failed");                                           \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
    } while (0)

#define vec_init_p(type, v) vec_init2_p(type, v, 4)
#define vec_init2_p(type, v, reserved)                                         \
    do {                                                                       \
        __vec_type_assert_p(type, v);                                          \
        (v)->size = 0;                                                         \
        (v)->capacity = (reserved);                                            \
        if (!((v)->data = malloc(sizeof(type) * (v)->capacity))) {             \
            perror("malloc failed");                                           \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
    } while (0)

#define vec_push(type, v, x)                                                   \
    do {                                                                       \
        __vec_type_assert(type, v);                                            \
        if ((v).size >= (v).capacity)                                          \
            vec_realloc(                                                       \
                type, v,                                                       \
                (v).capacity > 1 ? ((v).capacity + ((v).capacity >> 1)) : 2);  \
        (v).data[(v).size++] = x;                                              \
    } while (0)
#define vec_push_p(type, v, x)                                                 \
    do {                                                                       \
        __vec_type_assert_p(type, v);                                          \
        if ((v)->size >= (v)->capacity)                                        \
            vec_realloc_p(type, v,                                             \
                          (v)->capacity > 1                                    \
                              ? ((v)->capacity + ((v)->capacity >> 1))         \
                              : 2);                                            \
        (v)->data[(v)->size++] = x;                                            \
    } while (0)

#define vec_pop(v) (v).data[--(v).size]
#define vec_pop_p(v) (v)->data[--(v)->size]

#define vec_back(v) (v).data[(v).size - 1]
#define vec_back_p(v) (v)->data[(v)->size - 1]

#define vec_clear(v) (v).size = 0
#define vec_clear_p(v) (v)->size = 0

#define vec_empty(v) ((v).size == 0)
#define vec_empty_p(v) ((v)->size == 0)

#define vec_at(v, i)                                                           \
    ((i) < 0 || (i) >= (v).size                                                \
         ? (perror("vector index out of bounds"), exit(EXIT_FAILURE))          \
         : (v).data[i])
#define vec_at_p(v, i)                                                         \
    ((i) < 0 || (i) >= (v)->size                                               \
         ? (perror("vector index out of bounds"), exit(EXIT_FAILURE))          \
         : (v)->data[i])

#define vec_set(v, i, x)                                                       \
    ((i) < 0 || (i) >= (v).size                                                \
         ? (perror("vector index out of bounds"), exit(EXIT_FAILURE))          \
         : (v).data[i] = x)
#define vec_set_p(v, i, x)                                                     \
    ((i) < 0 || (i) >= (v)->size                                               \
         ? (perror("vector index out of bounds"), exit(EXIT_FAILURE))          \
         : (v)->data[i] = x)

#define vec_resize(type, v, n, def_val)                                        \
    do {                                                                       \
        __vec_type_assert(type, v);                                            \
        if ((n) > (v).capacity)                                                \
            vec_realloc(type, v, n);                                           \
        while ((v).size < (n))                                                 \
            (v).data[(v).size++] = (def_val);                                  \
        (v).size = (n);                                                        \
    } while (0)
#define vec_resize_p(type, v, n, def_val)                                      \
    do {                                                                       \
        __vec_type_assert_p(type, v);                                          \
        if ((n) > (v)->capacity)                                               \
            vec_realloc_p(type, v, n);                                         \
        while ((v)->size < (n))                                                \
            (v)->data[(v)->size++] = (def_val);                                \
        (v)->size = (n);                                                       \
    } while (0)

#define vec_shrink(type, v)                                                    \
    do {                                                                       \
        __vec_type_assert(type, v);                                            \
        if ((v).size != (v).capacity)                                          \
            vec_realloc(type, v, (v).size);                                    \
    } while (0)
#define vec_shrink_p(type, v)                                                  \
    do {                                                                       \
        __vec_type_assert_p(type, v);                                          \
        if ((v)->size != (v)->capacity)                                        \
            vec_realloc_p(type, v, (v)->size);                                 \
    } while (0)

#define vec_realloc(type, v, n)                                                \
    do {                                                                       \
        __vec_type_assert(type, v);                                            \
        if ((n) == (v).capacity)                                               \
            break;                                                             \
        if ((n) == 0) {                                                        \
            free((v).data);                                                    \
            (v).data = NULL;                                                   \
        } else if ((v).data == NULL) {                                         \
            (v).data = malloc(sizeof(type) * (n));                             \
            if (!(v).data) {                                                   \
                perror("malloc failed");                                       \
                exit(EXIT_FAILURE);                                            \
            }                                                                  \
        } else {                                                               \
            type *_newData = realloc((v).data, sizeof(type) * (n));            \
            if (!_newData) {                                                   \
                perror("realloc failed");                                      \
                exit(EXIT_FAILURE);                                            \
            }                                                                  \
            (v).data = _newData;                                               \
        }                                                                      \
        (v).capacity = (n);                                                    \
        if ((v).size > (n))                                                    \
            (v).size = (n);                                                    \
    } while (0)
#define vec_realloc_p(type, v, n)                                              \
    do {                                                                       \
        __vec_type_assert_p(type, v);                                          \
        if ((n) == (v)->capacity)                                              \
            break;                                                             \
        if ((n) == 0) {                                                        \
            free((v)->data);                                                   \
            (v)->data = NULL;                                                  \
        } else if ((v)->data == NULL) {                                        \
            (v)->data = malloc(sizeof(type) * (n));                            \
            if (!(v)->data) {                                                  \
                perror("malloc failed");                                       \
                exit(EXIT_FAILURE);                                            \
            }                                                                  \
        } else {                                                               \
            type *_newData = realloc((v)->data, sizeof(type) * (n));           \
            if (!_newData) {                                                   \
                perror("realloc failed");                                      \
                exit(EXIT_FAILURE);                                            \
            }                                                                  \
            (v)->data = _newData;                                              \
        }                                                                      \
        (v)->capacity = (n);                                                   \
        if ((v)->size > (n))                                                   \
            (v)->size = (n);                                                   \
    } while (0)

#define vec_reserve(type, v, n)                                                \
    do {                                                                       \
        __vec_type_assert(type, v);                                            \
        if ((n) > (v).capacity)                                                \
            vec_realloc(type, v, n);                                           \
    } while (0)
#define vec_reserve_p(type, v, n)                                              \
    do {                                                                       \
        __vec_type_assert_p(type, v);                                          \
        if ((n) > (v)->capacity)                                               \
            vec_realloc_p(type, v, n);                                         \
    } while (0)

#define vec_print(type, fn, v, indent)                                         \
    do {                                                                       \
        __vec_type_assert(type, v);                                            \
        if (!(v).data) {                                                       \
            printf(#type "([])");                                              \
            break;                                                             \
        }                                                                      \
        printf(#type "([");                                                    \
        if ((v).size == 0) {                                                   \
            printf("])");                                                      \
            break;                                                             \
        }                                                                      \
        putchar('\n');                                                         \
        for (int __i0 = 0; __i0 < (v).size; __i0++) {                          \
            ___vec_print_indent(indent);                                       \
            fn((v).data[__i0], (indent) + 2);                                  \
            if (__i0 < (v).size - 1)                                           \
                putchar(',');                                                  \
            putchar('\n');                                                     \
        }                                                                      \
        ___vec_print_indent((indent) - 1);                                     \
        putchar(']');                                                          \
        putchar(')');                                                          \
    } while (0)
#define vec_print_p(type, fn, v, indent)                                       \
    do {                                                                       \
        __vec_type_assert_p(type, v);                                          \
        if (!(v)->data)                                                        \
            break;                                                             \
        printf(#type "([");                                                    \
        if ((v).size == 0) {                                                   \
            printf("])");                                                      \
            break;                                                             \
        }                                                                      \
        putchar('\n');                                                         \
        for (int __i0 = 0; __i0 < (v)->size; __i0++) {                         \
            ___vec_print_indent(indent);                                       \
            fn((v)->data[__i0], (indent) + 2);                                 \
            if (__i0 < (v)->size - 1)                                          \
                putchar(',');                                                  \
            putchar('\n');                                                     \
        }                                                                      \
        ___vec_print_indent((indent) - 1);                                     \
        putchar(']');                                                          \
        putchar(')');                                                          \
    } while (0)

#define vec_free(v) free((v).data)
#define vec_free_p(v) free((v)->data)

#define vec_free2(v, fn)                                                       \
    do {                                                                       \
        if (!(v).data)                                                         \
            break;                                                             \
        for (int __i0 = 0; __i0 < (v).size; __i0++) {                          \
            fn((v).data[__i0]);                                                \
        }                                                                      \
        free((v).data);                                                        \
    } while (0)
#define vec_free2_p(v, fn)                                                     \
    do {                                                                       \
        if (!(v)->data)                                                        \
            break;                                                             \
        for (int __i0 = 0; __i0 < (v)->size; __i0++) {                         \
            fn((v)->data[__i0]);                                               \
        }                                                                      \
        free((v)->data);                                                       \
    } while (0)

#define vec_free_ap(v)                                                         \
    do {                                                                       \
        vec_free_p(v);                                                         \
        free(v);                                                               \
    } while (0)
#define vec_free2_ap(v, fn)                                                    \
    do {                                                                       \
        vec_free2_p(v, fn);                                                    \
        free(v);                                                               \
    } while (0)

#define ___vec_print_indent(indent)                                            \
    do {                                                                       \
        for (int __i1 = 0; __i1 < (indent) * 2; __i1++)                        \
            putchar(' ');                                                      \
    } while (0)

#if __STDC_VERSION__ >= 201112L
#define __vec_type_assert(type, var)                                       \
        _Static_assert(                                                        \
            sizeof(*((var).data)) == sizeof(type),                             \
            "Type of vector data does not match the expected type.")

    #define __vec_type_assert_p(type, var)                                     \
        _Static_assert(                                                        \
            sizeof(*((var)->data)) == sizeof(type),                            \
            "Type of vector data does not match the expected type.")
#else
#define __vec_type_assert(type, var) (0)
#define __vec_type_assert_p(type, var) (0)
#endif

#endif // VEC_H_LEGACY_DEFINED