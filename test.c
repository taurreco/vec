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
    int status, tmp;

    vec = vec_alloc(2, sizeof(int));
    
    tmp = 1;
    status = vec_push(vec, &tmp);
    TEST_ASSERT_EQUAL_INT(0, status);
    tmp = 2;
    status = vec_push(vec, &tmp);
    TEST_ASSERT_EQUAL_INT(0, status);
    tmp = 0;

    status = vec_get(vec, 0, &tmp);
    TEST_ASSERT_EQUAL_INT(1, tmp);
   
    status = vec_get(vec, 1, &tmp);
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
    int status, tmp;

    vec = vec_alloc(1, sizeof(int));
    tmp = 1;
    
    TEST_ASSERT_FALSE(vec->cap > 1);

    status = vec_push(vec, &tmp);
    TEST_ASSERT_EQUAL_INT(0, status);
    status = vec_push(vec, &tmp);
    TEST_ASSERT_EQUAL_INT(0, status);

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
    int status, tmp;

    vec = vec_alloc(4, sizeof(int));
    
    /* fill vec [1, 1, 3] */

    tmp = 1;
    status = vec_push(vec, &tmp);
    TEST_ASSERT_EQUAL(0, status);
    status = vec_push(vec, &tmp);
    TEST_ASSERT_EQUAL(0, status);
    tmp = 3;
    status = vec_push(vec, &tmp);
    TEST_ASSERT_EQUAL(0, status);
    
    TEST_ASSERT_EQUAL_INT(3, vec->len);

    status = vec_get(vec, 1, &tmp);
    TEST_ASSERT_EQUAL(0, status);
    TEST_ASSERT_EQUAL_INT(1, tmp);

    /**
     *  new insert 
     *     V    
     * [1, 2, 1, 3] 
     *
     */

    tmp = 2;
    status = vec_put(vec, &tmp, 1);
    TEST_ASSERT_EQUAL(0, status);

    /* use getters to assert vec state */

    status = vec_get(vec, 1, &tmp);
    TEST_ASSERT_EQUAL(0, status);
    TEST_ASSERT_EQUAL_INT(2, tmp);
    TEST_ASSERT_EQUAL_INT(4, vec->len);
    
    status = vec_get(vec, 2, &tmp);
    TEST_ASSERT_EQUAL(0, status);
    TEST_ASSERT_EQUAL_INT(1, tmp);
    
    status = vec_get(vec, 3, &tmp);
    TEST_ASSERT_EQUAL(0, status);
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
    int status, tmp;

    vec = vec_alloc(1, sizeof(int));

    tmp = 1;
    status = vec_push(vec, &tmp);
    TEST_ASSERT_EQUAL_INT(0, status);

    status = vec_get(vec, 0, &tmp); 
    TEST_ASSERT_EQUAL_INT(0, status);
    TEST_ASSERT_EQUAL_INT(1, tmp);
    TEST_ASSERT_EQUAL_INT(1, vec->len);
    
    tmp = 0;
    status = vec_pop(vec, &tmp);
    TEST_ASSERT_EQUAL_INT(0, status);
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
    struct vector *vec;
    int tmp;

    vec = vec_alloc(8, sizeof(int));
    
    tmp = 1;
    TEST_ASSERT_EQUAL_INT(0, vec_push(vec, &tmp));
    TEST_ASSERT_EQUAL_INT(0, vec_push(vec, &tmp));
    TEST_ASSERT_EQUAL_INT(0, vec_push(vec, &tmp));
    TEST_ASSERT_EQUAL_INT(0, vec_push(vec, &tmp));

    TEST_ASSERT_EQUAL_INT(8, vec->cap);
    
    TEST_ASSERT_EQUAL_INT(0, vec_pop(vec, NULL));
    TEST_ASSERT_EQUAL_INT(0, vec_pop(vec, NULL));
    TEST_ASSERT_EQUAL_INT(0, vec_pop(vec, NULL));
    TEST_ASSERT_EQUAL_INT(0, vec_pop(vec, NULL));

    TEST_ASSERT_EQUAL_INT(5, vec->cap);

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

    vec = vec_alloc(4, sizeof(int));

    tmp = 1;
    TEST_ASSERT_EQUAL_INT(0, vec_push(vec, &tmp));
    TEST_ASSERT_EQUAL_INT(0, vec_push(vec, &tmp));
    tmp = 2;
    TEST_ASSERT_EQUAL_INT(0, vec_push(vec, &tmp));
    
    TEST_ASSERT_EQUAL_INT(3, vec->len);

    TEST_ASSERT_EQUAL_INT(0, vec_get(vec, 1, &tmp));
    TEST_ASSERT_EQUAL_INT(1, tmp);

    tmp = 0;
    TEST_ASSERT_EQUAL_INT(0, vec_del(vec, 1, &tmp));
    TEST_ASSERT_EQUAL_INT(1, tmp);
    TEST_ASSERT_EQUAL_INT(2, vec->len);
    
    TEST_ASSERT_EQUAL_INT(0, vec_get(vec, 1, &tmp));
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

