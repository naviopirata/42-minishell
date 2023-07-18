#include "tests.h"

TEST_GROUP(mock);

TEST_SETUP(mock) {

}

TEST_TEAR_DOWN(mock) {

}

TEST(mock, check_fail) {

	TEST_FAIL();
}

TEST(mock, check_fail_msg) {

	TEST_FAIL_MESSAGE("Fails here!");
}

TEST_GROUP_RUNNER(mock) {
	RUN_TEST_CASE(mock, check_fail);
	RUN_TEST_CASE(mock, check_fail_msg);
}
