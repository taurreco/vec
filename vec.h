#ifndef VEC_H
#define VEC_H

/**********
 * vector *
 **********/

struct vector {
    char* data;
    int cap;
    int len;
    int stride;
};

/* construction / destruction */

struct vector* mkvec(int len, int stride);
void delvec(struct vector* vec);

/* insertion */

void vecset(struct vector* vec, void* src, int i);
void vecpush(struct vector* vec, void* src);
void vecadd(struct vector* vec, void* src, int i);

/* deletion */

void vecpop(struct vector* vec, void* dst);
void vecdel(struct vector* vec, int i);

/* retrieval */

void vecget(struct vector* vec, int i, void* dst);
void vectop(struct vector* vec, void* dst);
void vecback(struct vector* vec, void* dst);

#endif    /* VEC_H */
