#ifndef VEC_H
#define VEC_H

#include <stdint.h>

/**********
 * vector *
 **********/

struct vector {
    void (*val_free)(void *);
    uintptr_t *data;
    int cap;
    int len;
};

/* construction / destruction */

struct vector * vec_alloc(int cap, void (*val_free)(void *));
void vec_free(struct vector *vec);

/* insertion */

void vec_set(struct vector *vec, uintptr_t src, int idx);
void vec_push(struct vector *vec, uintptr_t src);
void vec_put(struct vector *vec, uintptr_t src, int idx);

/* deletion */

uintptr_t vec_pop(struct vector *vec);
uintptr_t vec_del(struct vector *vec, int idx);

/* retrieval */

uintptr_t vec_get(struct vector *vec, int idx);

/* utility */

int vec_len(struct vector *vec);

#endif    /* VEC_H */
