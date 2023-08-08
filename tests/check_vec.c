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
 *                                                       *
 *                                                                   *
 *********************************************************************/

/**********
 * simple *
 **********/

void
basic()
{
    struct vector* vec;
    int one;
    int two;
    int tmp;

    vec = mkvec(2, sizeof(int));
    one = 1;
    two = 2;

    vecpush(vec, &one);
    vecpush(vec, &two);

    vecget(vec, 0, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);

    vecget(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(two, tmp);
    
    delvec(vec);
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
    int tmp;

    vec = mkvec(1, sizeof(int));
    one = 1;
    two = 2;

    vecpush(vec, &one);
    vecpush(vec, &two);

    TEST_ASSERT_TRUE(vec->cap > 1);
    TEST_ASSERT_EQUAL_INT(2, vec->len);

    delvec(vec);
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

    vec = mkvec(4, sizeof(int));
    one = 1;
    two = 2;
    three = 3;

    vecpush(vec, &one);
    vecpush(vec, &one);
    vecpush(vec, &three);

    vecget(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);

    vecadd(vec, &two, 1);

    vecget(vec, 1, &tmp);
    TEST_ASSERT_EQUAL_INT(two, tmp);

    TEST_ASSERT_EQUAL_INT(4, vec->len);
    
    vecget(vec, 2, &tmp);
    TEST_ASSERT_EQUAL_INT(one, tmp);
    
    vecget(vec, 3, &tmp);
    TEST_ASSERT_EQUAL_INT(three, tmp);
    
    delvec(vec);
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
    RUN_TEST(basic);
    RUN_TEST(basic_grow);
    RUN_TEST(basic_add);
    return UNITY_END();
}

