#ifndef VEC_H
#define VEC_H

/**********
 * vector *
 **********/

struct VECTOR {
    char* data;
    int cap;
    int len;
    int stride;
};

/* construction / destruction */

struct VECTOR* mkvec(int cap, int stride);
void delvec(struct VECTOR* vec);

/* insertion */

void vecset(struct VECTOR* vec, void* src, int idx);
void vecpush(struct VECTOR* vec, void* src);
void vecadd(struct VECTOR* vec, void* src, int idx);

/* deletion */

void vecpop(struct VECTOR* vec, void* dst);
void vecdel(struct VECTOR* vec, int idx, void* dst);

/* retrieval */

void vecget(struct VECTOR* vec, int idx, void* dst);

/* utility */

int veclen(struct VECTOR* vec);

#endif    /* VEC_H */
