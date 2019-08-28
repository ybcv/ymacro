#include <stdio.h>

#include "../y.h"

#define TEST(str, cond) if (!(cond)) printf("FAILED %s:%d:%s %d: %s\n", __FILE__, __LINE__, __func__, cond, str)

int main (int argc, const char* argv[argc]) 
{

//
//y_aid.h
//

Y_EVAL(TEST Y_LIST("EVAL", 1));

#if Y_EVAL(Y_IS_EMPTY Y_LIST())
	TEST("LS EMPTY", 1);
#else
	TEST("LS EMPTY", 0);
#endif

#if Y_EVAL(Y_IS_EMPTY Y_HEAD(Y_LIST())) 
	TEST("LS EMPTY", 1); 
#else 
	TEST("LS EMPTY", 0); 
#endif

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wunused-value\"")
	TEST("HEAD",              1 == Y_HEAD(1,2,3));
	TEST("HEAD_LS",           1 == Y_EVAL(Y_HEAD_LS(1,2,3)));
	TEST("TAIL HEAD_LS",      1 == Y_EVAL(Y_IS_EMPTY Y_TAIL Y_HEAD_LS (1,2,3)));
	TEST("HEAD(TAIL)",        2 == Y_HEAD Y_TAIL(1,2,3));
	TEST("HEAD(TAIL(TAIL))",  3 == Y_EVAL(Y_HEAD Y_TAIL Y_TAIL(1,2,3)));
	TEST("HEAD(TAIL2)",       3 == Y_HEAD Y_TAIL2 (1,2,3));
	TEST("HEAD(HEAD2)",       1 == Y_HEAD Y_HEAD2 (1,2,3));
	TEST("HEAD(TAIL(HEAD2))", 2 == Y_EVAL(Y_HEAD Y_TAIL Y_HEAD2 (1,2,3)));
	TEST("UNSHIFT",           4 == Y_HEAD Y_UNSHIFT(4, ()));
_Pragma("GCC diagnostic pop")

//
//y_arg.h
//

TEST("ARG COUNT 0",   0 == Y_COUNT());
TEST("ARG COUNT 1",   1 == Y_COUNT(1));
TEST("ARG COUNT 2",   2 == Y_COUNT(1,2));
TEST("ARG COUNT 15", 15 == Y_COUNT(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15));
TEST("ARG COUNT 30", 30 == Y_COUNT(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30));
TEST("ARG COUNT 31", 31 == Y_COUNT(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31));
TEST("ARG COUNT 32", 32 == Y_COUNT(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32));
TEST("ARG COUNT 33", 33 == Y_COUNT(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33));
TEST("ARG COUNT 34", Y_COUNT(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34));

//
//y_mapreduce.h
//
#define TEST_EACH(x) TEST("EACH", x);
Y_EACH(TEST_EACH, (1))
Y_EACH(TEST_EACH, (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32))

struct S { int key; const char* name; size_t timestamp; };
#define OFFSET_S(x) offsetof(struct S, x),
size_t offsets[] = { Y_EACH(OFFSET_S, (key, name, timestamp)) 0 };
TEST("EACH", offsetof(struct S, key) == offsets[0] &&
             offsetof(struct S, name) == offsets[1] &&
             offsetof(struct S, timestamp) == offsets[2]);
TEST("OFFSET[key]", 0 == (int)offsets[0]);
TEST("OFFSET[name]", (int)offsets[1]);
TEST("OFFSET[timestamp]", (int)offsets[2]);

#define INCR(x) INCR_(x)
#define INCR_(x) (1+x)
#define MUL(a,b) MUL_(a,b)
#define MUL_(a,b) a*b
TEST("REDUCE(MAP)", 2*3*4*5*6*7*8 == Y_REDUCE(MUL, Y_MAP(INCR, (1,2,3,4,5,6,7))));

}
