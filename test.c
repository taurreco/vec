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
    struct vector* vec;
    int one;
    int two;
    int tmp;

    vec = vec_alloc(2, sizeof(int));
    one = 1;
    two = 2;

    vec_push(vec, &one);
    vec_push(vec, &two);

    vec_get(vec, 0, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);

    vec_get(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(two, tmp);
    
    vec_free(vec);
}

/**************
 * basic_grow *
 **************/

void
basic_grow()
{
    struct vector* vec;
    int one;
    int two;

    vec = vec_alloc(1, sizeof(int));
    one = 1;
    two = 2;

    vec_push(vec, &one);
    vec_push(vec, &two);

    TEST_ASSERT_TRUE(vec->cap > 1);
    TEST_ASSERT_EQUAL_INT(2, vec->len);

    vec_free(vec);
}

/*************
 * basic_add *
 *************/

void
basic_add()
{
    struct vector* vec;
    int one;
    int two;
    int three;
    int tmp;

    vec = vec_alloc(4, sizeof(int));
    one = 1;
    two = 2;
    three = 3;

    vec_push(vec, &one);
    vec_push(vec, &one);
    vec_push(vec, &three);
    
    TEST_ASSERT_EQUAL_INT(3, vec->len);

    vec_get(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);

    vec_add(vec, &two, 1);

    vec_get(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(two, tmp);
    TEST_ASSERT_EQUAL_INT(4, vec->len);
    
    vec_get(vec, 2, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);
    
    vec_get(vec, 3, &tmp);
    TEST_ASSERT_EQUAL_INT(three, tmp);
    
    vec_free(vec);
}

/*************
 * basic_pop *
 *************/

void
basic_pop()
{
    struct vector* vec;
    int one;
    int tmp;

    vec = vec_alloc(1, sizeof(int));
    one = 1;

    vec_push(vec, &one);

    vec_get(vec, 0, &tmp); 
    TEST_ASSERT_EQUAL_INT(one, tmp);
    TEST_ASSERT_EQUAL_INT(1, vec->len);

    tmp = 0;

    vec_pop(vec, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);
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
    int one;

    vec = vec_alloc(4, sizeof(int));
    one = 1;

    vec_push(vec, &one);
    vec_push(vec, &one);
    vec_push(vec, &one);
    vec_push(vec, &one);

    TEST_ASSERT_EQUAL_INT(4, vec->cap);
    
    vec_pop(vec, 0);
    vec_pop(vec, 0);
    vec_pop(vec, 0);

    TEST_ASSERT_EQUAL_INT(3, vec->cap);

    vec_free(vec);
}

/*************
 * basic_del *
 *************/

void
basic_del()
{
    struct vector* vec;
    int one;
    int two;
    int tmp;

    vec = vec_alloc(4, sizeof(int));
    one = 1;
    two = 2;

    vec_push(vec, &one);
    vec_push(vec, &one);
    vec_push(vec, &two);
    
    TEST_ASSERT_EQUAL_INT(3, vec->len);

    vec_get(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);

    vec_del(vec, 1, 0);
    TEST_ASSERT_EQUAL_INT(2, vec->len);
    
    vec_get(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(two, tmp);
    
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
    RUN_TEST(basic_add);
    RUN_TEST(basic_pop);
    RUN_TEST(basic_shrink);
    RUN_TEST(basic_del);
    return UNITY_END();
}

