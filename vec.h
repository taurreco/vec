#ifndef VEC_H
#define VEC_H

/**********
 * vector *
 **********/

typedef struct {
    char* data;
    int cap;
    int len;
    int stride;
} VECTOR;

/* construction / destruction */

VECTOR* mkvec(int cap, int stride);
void delvec(VECTOR* vec);

/* insertion */

void vecset(VECTOR* vec, void* src, int idx);
void vecpush(VECTOR* vec, void* src);
void vecadd(VECTOR* vec, void* src, int idx);

/* deletion */

void vecpop(VECTOR* vec, void* dst);
void vecdel(VECTOR* vec, int idx, void* dst);

/* retrieval */

void vecget(VECTOR* vec, int idx, void* dst);

/* utility */

int veclen(VECTOR* vec);

#endif    /* VEC_H */
