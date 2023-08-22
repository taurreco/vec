#ifndef VEC_H
#define VEC_H

#include <stdint.h>

/**********
 * vector *
 **********/

struct vector {
    uint8_t* data;
    int cap;
    int len;
    int stride;
};

/* construction / destruction */

struct vector* vec_alloc(int cap, int stride);
void vec_free(struct vector* vec);

/* insertion */

void vec_set(struct vector* vec, void* src, int idx);
void vec_push(struct vector* vec, void* src);
void vec_put(struct vector* vec, void* src, int idx);

/* deletion */

void vec_pop(struct vector* vec, void* dst);
void vec_del(struct vector* vec, int idx, void* dst);

/* retrieval */

void vec_get(struct vector* vec, int idx, void* dst);

/* utility */

int vec_len(struct vector* vec);

#endif    /* VEC_H */
