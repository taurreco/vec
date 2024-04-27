#include "vec.h"
#include "unity.h"

/*********************************************************************
 *                                                                   *
 *                          unity helpers                            *
 *                                                                   *
 *********************************************************************/

void 
setUp() 
{
    /* empty */
}

void 
tearDown() 
{
    /* empty */
}

/*********************************************************************
 *                                                                   *
 *                           basic tests                             *
 *                                                                   *
 *********************************************************************/

/**************
 * basic_push *
 **************/

void
basic_push()
{
    struct vector *vec;
    int tmp;

    vec = vec_alloc(2, 0);

    vec_push(vec, 1);
    vec_push(vec, 2);

    tmp = vec_get(vec, 0);
    TEST_ASSERT_EQUAL_INT(1, tmp);

    tmp = vec_get(vec, 1);
    TEST_ASSERT_EQUAL_INT(2, tmp);
    
    vec_free(vec);
}

/**************
 * basic_grow *
 **************/

void
basic_grow()
{
    struct vector *vec;

    vec = vec_alloc(1, 0);

    vec_push(vec, 1);
    vec_push(vec, 1);

    TEST_ASSERT_TRUE(vec->cap > 1);
    TEST_ASSERT_EQUAL_INT(2, vec->len);

    vec_free(vec);
}

/*************
 * basic_put *
 *************/

void
basic_put()
{
    struct vector *vec;
    int tmp;

    vec = vec_alloc(4, 0);

    vec_push(vec, 1);
    vec_push(vec, 2);
    vec_push(vec, 3);
    
    TEST_ASSERT_EQUAL_INT(3, vec->len);

    tmp = vec_get(vec, 1);
    TEST_ASSERT_EQUAL_INT(1, tmp);

    vec_put(vec, 2, 1);

    tmp = vec_get(vec, 1);
    TEST_ASSERT_EQUAL_INT(2, tmp);
    TEST_ASSERT_EQUAL_INT(4, vec->len);
    
    tmp = vec_get(vec, 2);
    TEST_ASSERT_EQUAL_INT(1, tmp);
    
    tmp = vec_get(vec, 3);
    TEST_ASSERT_EQUAL_INT(3, tmp);
    
    vec_free(vec);
}

/*************
 * basic_pop *
 *************/

void
basic_pop()
{
    struct vector *vec;
    int tmp;

    vec = vec_alloc(1, 0);

    vec_push(vec, 1);

    tmp = vec_get(vec, 0); 
    
    TEST_ASSERT_EQUAL_INT(1, tmp);
    TEST_ASSERT_EQUAL_INT(1, vec->len);
    
    tmp = 0;
    tmp = vec_pop(vec);

    TEST_ASSERT_EQUAL_INT(1, tmp);
    TEST_ASSERT_EQUAL_INT(0, vec->len);

    vec_free(vec);
}

/****************
 * basic_shrink *
 ****************/

void
basic_shrink()
{
    struct vector* vec;

    vec = vec_alloc(4, 0);

    vec_push(vec, 1);
    vec_push(vec, 1);
    vec_push(vec, 1);
    vec_push(vec, 1);

    TEST_ASSERT_EQUAL_INT(4, vec->cap);
    
    vec_pop(vec);
    vec_pop(vec);
    vec_pop(vec);

    TEST_ASSERT_EQUAL_INT(3, vec->cap);

    vec_free(vec);
}

/*************
 * basic_del *
 *************/

void
basic_del()
{
    struct vector *vec;
    int tmp;

    vec = vec_alloc(4, 0);

    vec_push(vec, 1);
    vec_push(vec, 1);
    vec_push(vec, 2);
    
    TEST_ASSERT_EQUAL_INT(3, vec->len);

    tmp = vec_get(vec, 1);
    TEST_ASSERT_EQUAL_INT(1, tmp);

    vec_del(vec, 1);
    TEST_ASSERT_EQUAL_INT(2, vec->len);
    
    tmp = vec_get(vec, 1);
    TEST_ASSERT_EQUAL_INT(2, tmp);
    
    vec_free(vec);
}


/*********************************************************************
 *                                                                   *
 *                              main                                 *
 *                                                                   *
 *********************************************************************/

/********
 * main *
 ********/

int
main() 
{
    UNITY_BEGIN();
    RUN_TEST(basic_push);
    RUN_TEST(basic_grow);
    RUN_TEST(basic_put);
    RUN_TEST(basic_pop);
    RUN_TEST(basic_shrink);
    RUN_TEST(basic_del);
    return UNITY_END();
}

