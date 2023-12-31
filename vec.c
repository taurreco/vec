#include "vec.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*********************************************************************
 *                                                                   *
 *                    constructor / destructor                       *
 *                                                                   *
 *********************************************************************/

/*************
 * vec_alloc *
 *************/

struct vector*
vec_alloc(int cap, int stride)
{
    struct vector* vec;
    char* data;
    
    vec = malloc(sizeof(struct vector));
    data = malloc(cap * stride);

    vec->data = data;
    vec->cap = cap;
    vec->len = 0;
    vec->stride = stride;

    return vec;
}

/************
 * vec_free *
 ************/

void
vec_free(struct vector* vec)
{
    free(vec->data);
    free(vec);
}

/*********************************************************************
 *                                                                   *
 *                             utility                               *
 *                                                                   *
 *********************************************************************/

/**********
 * resize *
 **********/

/* changes size of vector */

void
resize(struct vector* vec, int new_cap)
{
    char* new_data;
    char* tmp;

    new_data = malloc(new_cap * vec->stride);
    tmp = vec->data;
    
    memcpy(new_data, vec->data, vec->len * vec->stride);
    vec->data = new_data;
    vec->cap = new_cap;
    
    free(tmp);
}

/***********
 * vec_len *
 ***********/

int
vec_len(struct vector* vec)
{
    return vec->len;
}

/*********************************************************************
 *                                                                   *
 *                            insertion                              *
 *                                                                   *
 *********************************************************************/

/***********
 * vec_set *
 ***********/

/* updates existing item */

void
vec_set(struct vector* vec, void* src, int idx)
{
    memcpy(vec->data + idx * vec->stride, src, vec->stride);
}

/************
 * vec_push *
 ************/

/* pushes item to the back of the vector */

void
vec_push(struct vector* vec, void* src)
{
    if (vec->len == vec->cap)
        resize(vec, vec->cap * 2);    

    vec->len++;

    vec_set(vec, src, vec->len - 1);
}

/***********
 * vec_put *
 ***********/

/* inserts an item at an index */

void
vec_put(struct vector* vec, void* src, int idx)
{
    int bytes;
    char* start;
    
    if (vec->len == vec->cap)
        resize(vec, vec->cap * 2);

    bytes = (vec->len - idx) * vec->stride;
    start = vec->data + idx * vec->stride;

    memmove(start + vec->stride, start, bytes);
    vec_set(vec, src, idx);
    
    vec->len++;
}

/*********************************************************************
 *                                                                   *
 *                             deletion                              *
 *                                                                   *
 *********************************************************************/

/***********
 * vec_pop *
 ***********/

/* removes the last item in the vector, copies it to dst */

void
vec_pop(struct vector* vec, void* dst)
{
    if (vec->len < 3 * vec->cap / 4)
        resize(vec, 3 * vec->cap / 4);
    
    if (dst)
    	memcpy(dst, vec->data + (vec->len - 1) * vec->stride, vec->stride);
    
    vec->len--;
}

/***********
 * vec_del *
 ***********/

/* deletes an item at an index */

void
vec_del(struct vector* vec, int idx, void* dst)
{
    int bytes;
    char* start;
    
    if (vec->len < 3 * vec->cap / 4)
        resize(vec, 3 * vec->cap / 4);
        
    bytes = (vec->len - idx) * vec->stride;
    start = vec->data + idx * vec->stride;
    
    if (dst)
    	memcpy(dst, start, vec->stride);

    memmove(start, start + vec->stride, bytes);
    
    vec->len--;
}

/*********************************************************************
 *                                                                   *
 *                            retrieval                              *
 *                                                                   *
 *********************************************************************/

/***********
 * vec_get *
 ***********/

/* copies the item at an index to dst */

void
vec_get(struct vector* vec, int idx, void* dst)
{
    memcpy(dst, vec->data + idx * vec->stride, vec->stride);
}

