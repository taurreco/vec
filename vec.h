#ifndef VEC_H
#define VEC_H

#include <stdint.h>

#define DEFAULT_CAP 5

/**********
 * vector *
 **********/

struct vector {
    uint8_t *data;
    int cap;         /* total space in strides */
    int len;         /* length in strides */
    int stride;      /* unit length of data in bytes */
};

/* construction / destruction */

struct vector * vec_alloc(int cap, int stride);
void vec_free(struct vector *vec);

/* insertion */

int vec_set(struct vector *vec, uint8_t *src, int idx);
int vec_push(struct vector *vec, uint8_t *src);
int vec_put(struct vector *vec, uint8_t *src, int idx);

/* deletion */

int vec_pop(struct vector *vec, uint8_t *dest);
int vec_del(struct vector *vec, int idx, uint8_t *out);

/* retrieval */

int vec_get(struct vector *vec, int idx, uint8_t *out);

/* utility */

int vec_len(struct vector *vec);

#endif    /* VEC_H */
