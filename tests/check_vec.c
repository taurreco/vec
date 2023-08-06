#include "rcc.h"
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
 *                         token correctness                         *
 *                                                                   *
 *********************************************************************/

/*******
 * add *
 *******/

void
add()
{
    char data[10];
    struct exp* exp;
    struct exp* act;
    int one;

    one = 1;
    struct buffer buf = { data, 0 };

    exp = mkexp(E_BINOP, mkbinop(O_ADD, mkexp(E_INT, &one), mkexp(E_INT, &one)));
    act = parse("1 + 1", &buf);

    TEST_ASSERT_TRUE(expeq(exp, act));

    delexp(exp);
    delexp(act);
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
    RUN_TEST(add);
    return UNITY_END();
}

