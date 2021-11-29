#include "Unity/unity.h"
#include "funcao_1.h"

void setUp(){};

void tearDown(){};

void test_funcao(){
        TEST_ASSERT_EQUAL(1,entrada('n'));
}

int main(void){

        UNITY_BEGIN();
        RUN_TEST(test_funcao);
        return UNITY_END();

}