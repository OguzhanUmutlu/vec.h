#ifndef VEC_H_DEFINED
#define VEC_H_DEFINED

#define vec(type)                                                              \
    struct {                                                                   \
        int size, capacity;                                                    \
        type *data;                                                            \
    }
#define vec_init(type, v, reserved)                                            \
    do {                                                                       \
        (v).size = 0;                                                          \
        (v).capacity = (reserved);                                             \
        (v).data = malloc(sizeof(type) * (v).capacity);                        \
        if (!(v).data) {                                                       \
            perror("malloc failed");                                           \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
    } while (0)
#define vec_create(type, reserved)                                             \
    {                                                                          \
        vec(type) _v;                                                          \
        vec_init(_v);                                                          \
        _v;                                                                    \
    }
#define vec_push(type, v, x)                                                   \
    do {                                                                       \
        if ((v).size >= (v).capacity)                                          \
            vec_reserve(type, v,                                               \
                        (v).capacity > 1 ? (v).capacity + (v).capacity >> 1    \
                                         : 2);                                 \
        (v).data[(v).size++] = x;                                              \
    } while (0)
#define vec_pop(v) (v).data[--v.size]
#define vec_back(v) (v).data[v.size - 1]
#define vec_clear(v) (v).size = 0
#define vec_empty(v) ((v).size == 0)
#define vec_at(v, i)                                                           \
    {                                                                          \
        if ((i) < 0 || (i) >= v.size) {                                        \
            perror("vector index out of bounds");                              \
            exit(1);                                                           \
        }                                                                      \
        (v).data[i];                                                           \
    }

#define vec_resize(type, v, n, def_val)                                        \
    do {                                                                       \
        if ((n) > (v).capacity)                                                \
            vec_realloc(type, v, n);                                           \
        while ((v).size < (n))                                                 \
            (v).data[(v).size++] = (def_val);                                  \
        (v).size = (n);                                                        \
    } while (0)
#define vec_shrink(type, v)                                                    \
    do {                                                                       \
        if ((v).size != (v).capacity)                                          \
            vec_realloc(type, v, v.size);                                      \
    } while (0)
#define vec_realloc(type, v, n)                                                \
    do {                                                                       \
        if ((n) == (v).capacity) break;                                        \
        type *_newData = realloc((v).data, sizeof(type) * (n));                \
        if (!_newData && (n) > 0) {                                            \
            perror("realloc failed");                                          \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
        (v).data = _newData;                                                   \
        (v).capacity = (n);                                                    \
        if ((v).size > (n))                                                    \
            (v).size = (n);                                                    \
    } while (0)
#define vec_reserve(type, v, n)                                                \
    do {                                                                       \
        if ((n) > (v).capacity)                                                \
            vec_realloc(type, v, n);                                           \
    } while (0)
#define vec_print(type, fn, v, indent)                                         \
    do {                                                                       \
        if (!(v).data)                                                         \
            return;                                                            \
        printf(#type "([");                                                    \
        if ((v).size != 0)                                                     \
            putchar('\n');                                                     \
        for (int i = 0; i < (v).size; i++) {                                   \
            print_indent(indent);                                              \
            fn((v).data[i], (indent) + 2);                                     \
            if (i < (v).size - 1)                                              \
                putchar(',');                                                  \
            putchar('\n');                                                     \
        }                                                                      \
        print_indent((indent) - 1);                                            \
        putchar(']');                                                          \
        putchar(')');                                                          \
    } while (0)
#define vec_free(v) free(v.data)
#define vec_free2(v, fn)                                                       \
    do {                                                                       \
        if (!v.data)                                                           \
            return;                                                            \
        for (int i = 0; i < v.size; i++) {                                     \
            fn(v.data[i]);                                                     \
        }                                                                      \
        free(v.data);                                                          \
    } while (0)

#endif // VEC_H_DEFINED
