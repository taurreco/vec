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

struct vector *
vec_alloc(int cap, int stride)
{
    struct vector *vec;
    uint8_t *data;

    if (stride <= 0)
        return NULL;

    if (cap < 0)
        return NULL;

    /* unspecified cap */
    if (cap == 0)
        cap = DEFAULT_CAP;
    
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
vec_free(struct vector *vec)
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

static void
resize(struct vector *vec, int new_cap)
{
    uint8_t *new_data, *tmp;

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
vec_len(struct vector *vec)
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

int
vec_set(struct vector *vec, void *src, int idx)
{
    if (src == NULL)
        return -1;

    if (idx < 0 || idx >= vec->len)
        return -1;

    memcpy(vec->data + idx * vec->stride, src, vec->stride);
    return 0;
}

/************
 * vec_push *
 ************/

/* pushes item to the back of the vector */

int
vec_push(struct vector *vec, void *src)
{
    uint8_t *dest;

    if (src == NULL)
        return -1;

    if (vec->len > 2 * vec->cap / 3)
        resize(vec, 2 * vec->cap); 

    vec->len++;

    dest = vec->data + (vec->len - 1) * vec->stride;
    memcpy(dest, src, vec->stride);
    
    return 0;
}

/***********
 * vec_put *
 ***********/

/* inserts an item at an index */

int
vec_put(struct vector *vec, void *src, int idx)
{
    int len;
    uint8_t *start;

    if (src == NULL)
        return -1;

    if (idx < 0 || idx >= vec->len)
        return -1;

    if (vec->len > 2 * vec->cap / 3)
        resize(vec, 2 * vec->cap);

    len = (vec->len - idx) * vec->stride;    /* length past index */
    start = vec->data + idx * vec->stride;

    memmove(start + vec->stride, start, len);
    memcpy(start, src, vec->stride);
    vec->len++;

    return 0;
}

/*********************************************************************
 *                                                                   *
 *                             deletion                              *
 *                                                                   *
 *********************************************************************/

/***********
 * vec_pop *
 ***********/

/* removes the last item in the vector, copies it to out */

int 
vec_pop(struct vector *vec, void *out)
{
    uint8_t *src;
    
    if (vec->len == 0)
        return -1;
    
    if (vec->len < vec->cap / 3)
        resize(vec, 2 * vec->cap / 3);
    
    src = vec->data + (vec->len - 1) * vec->stride;
    
    if (out != NULL)
        memcpy(out, src, vec->stride);
    
    vec->len--;
    
    return 0;
}

/***********
 * vec_del *
 ***********/

/* deletes an item at an index */

int
vec_del(struct vector *vec, int idx, void *out)
{
    int len;
    uint8_t *start;
    
    if (vec->len == 0)
        return -1;

    if (vec->len < vec->cap / 3)
        resize(vec, 2 * vec->cap / 3);
        
    len = vec->len - idx;
    start = vec->data + idx * vec->stride;

    if (out != NULL)
        memcpy(out, start, vec->stride);

    memmove(start, start + vec->stride, len * vec->stride);
    
    vec->len--;

    return 0;
}

/*********************************************************************
 *                                                                   *
 *                            retrieval                              *
 *                                                                   *
 *********************************************************************/

/***********
 * vec_get *
 ***********/

/* copies the item at an index to out */

int
vec_get(struct vector *vec, int idx, void* out)
{
    if (idx < 0 || idx >= vec->len)
        return -1;

    memcpy(out, vec->data + idx * vec->stride, vec->stride);

    return 0;
}

