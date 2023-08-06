#include "vec.h"
#include <stdlib.h>
#include <assert.h>

/*********************************************************************
 *                                                                   *
 *                    constructor / destructor                       *
 *                                                                   *
 *********************************************************************/

/*********
 * mkvec *
 *********/

struct vector*
mkvec(int len, int stride)
{
    struct vector* vec;
    char* data;
    
    vec = malloc(sizeof(struct vector));
    data = malloc(len * stride);

    vec->data = data;
    vec->cap = len;
    vec->len = len;
    vec->stride = stride;
}

/**********
 * delvec *
 **********/

void
delvec(struct vector* vec)
{
    free(vec->data);
    free(vec);
}

/*********************************************************************
 *                                                                   *
 *                             utility                               *
 *                                                                   *
 *********************************************************************/

/*********************************************************************
 *                                                                   *
 *                            insertion                              *
 *                                                                   *
 *********************************************************************/

/***********
 * vecpush *
 ***********/

/* pushes item to the back of the vector */

void
vecset(struct vector* vec, void* src, int i)
{
    assert(vec);
    assert(src);
    assert(vec->cap > vec->len);
    assert(vec->len);
    assert(vec->len > i);

    memcpy(vec->data + i * vec->stride, src, vec->stride);
}

/***********
 * vecpush *
 ***********/

/* pushes item to the back of the vector */

void
vecpush(struct vector* vec, void* src);
{
    assert(vec);
    assert(src);
    assert(vec->cap >= vec->len);
    
    if (vec->cap == vec->len) {
    
    }

    vecset(vec, src, vec->len - 1);
}
