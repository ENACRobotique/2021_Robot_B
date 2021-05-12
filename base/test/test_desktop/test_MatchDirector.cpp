#include "unity.h"
#include "ai/MatchDirector.h"

void test_abs_to_local()
{
    MatchDirector::isDrivingBackward = false;
    MatchDirector::isStartingLeft = true;
}
void setup() {
    #define DEBUG_NO_ARDUINO
    UNITY_BEGIN();
    RUN_TEST(test_abs_to_local);
    UNITY_END();

}
