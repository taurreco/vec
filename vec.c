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
vec_alloc(int cap, void (*val_free)(void *))
{
    struct vector *vec;
    uintptr_t *data;
    
    vec = malloc(sizeof(struct vector));
    data = malloc(cap * sizeof(uintptr_t));

    vec->val_free = val_free;
    vec->data = data;
    vec->cap = cap;
    vec->len = 0;

    return vec;
}

/************
 * vec_free *
 ************/

void
vec_free(struct vector *vec)
{
    if (vec->val_free) {
        for (int i = 0; i < vec->cap; i++) {
            if (vec->data[i])
                vec->val_free((void *)vec->data[i]);
        }
    }

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
resize(struct vector *vec, int new_cap)
{
    uintptr_t *new_data, *tmp;

    new_data = malloc(new_cap * sizeof(uintptr_t));
    tmp = vec->data;
    
    memcpy(new_data, vec->data, vec->len * sizeof(uintptr_t));
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

void
vec_set(struct vector *vec, uintptr_t src, int idx)
{
    if (vec->val_free) {
        if (vec->data[idx])
            vec->val_free((void *)vec->data[idx]);
    }

    vec->data[idx] = src;
}

/************
 * vec_push *
 ************/

/* pushes item to the back of the vector */

void
vec_push(struct vector *vec, uintptr_t src)
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
vec_put(struct vector *vec, uintptr_t src, int idx)
{
    int len;
    uintptr_t *start;
    
    if (vec->len == vec->cap)
        resize(vec, vec->cap * 2);

    len = (vec->len - idx);    /* length past idx */
    start = vec->data + idx;

    memmove(start + 1, start, len * sizeof(uintptr_t));
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

uintptr_t 
vec_pop(struct vector *vec)
{
    uintptr_t res;

    if (vec->len < 3 * vec->cap / 4)
        resize(vec, 3 * vec->cap / 4);
    
    res = vec->data[vec->len - 1];
    
    vec->len--;

    return res;
}

/***********
 * vec_del *
 ***********/

/* deletes an item at an index */

uintptr_t
vec_del(struct vector *vec, int idx)
{
    int len;
    uintptr_t *start, res;
    
    if (vec->len < 3 * vec->cap / 4)
        resize(vec, 3 * vec->cap / 4);
        
    len = (vec->len - idx);
    start = vec->data + idx;
    
    res = vec->data[idx];

    memmove(start, start + 1, len * sizeof(uintptr_t ));
    
    vec->len--;

    return res;
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

uintptr_t 
vec_get(struct vector *vec, int idx)
{
    return vec->data[idx];    
}

