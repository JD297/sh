#ifndef JD297_VEC_H
#define JD297_VEC_H

#include <stddef.h>

typedef struct {
    void **elements;
    size_t len;
    size_t num;
} vector_t;

#define VEC_RESIZE_FACTOR 2

extern int vec_init(vector_t *vec);

extern void vec_free(vector_t *vec);

extern int vec_push_back(vector_t *vec, void *el);

#define vec_size(vec_ptr) (vec_ptr)->num

#define vec_capacity(vec_ptr) (vec_ptr)->len

#define vec_set(vec_ptr, index, value) (vec_ptr)->elements[(index)] = (value)

#define vec_at(vec_ptr, index) (vec_ptr)->elements[(index)]

#define vec_at_last(vec_ptr) (vec_ptr)->elements[(vec_ptr)->num > 0 ? (vec_ptr)->num- 1 : 0]

#define vec_begin(vec_ptr) (vec_ptr)->elements

#define vec_end(vec_ptr) (vec_ptr)->elements[(vec_ptr)->num]

#endif

#ifdef JD297_VEC_IMPLEMENTATION

#include <stdlib.h>

int vec_init(vector_t *vec)
{
    vec->len = 1;
	vec->num = 0;
	vec->elements = (void **)calloc(vec->len, sizeof(void *));

	if (vec->elements == NULL) {
		return -1;
	}

    return 0;
}

void vec_free(vector_t *vec)
{
    free(vec->elements);
}

int vec_push_back(vector_t *vec, void *el)
{
    if (vec->num == vec->len) {
        size_t new_len = vec->len * VEC_RESIZE_FACTOR;

        vec->elements = (void **)realloc(vec->elements, new_len * sizeof(void *));

        if (vec->elements == NULL) {
            return -1;
        }

        vec->len = new_len;
    }

    vec->elements[vec->num++] = el;

    return 0;
}

#endif
