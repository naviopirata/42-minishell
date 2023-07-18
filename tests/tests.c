#include "tests.h"

void	run_all_tests(void)
{
	RUN_TEST_GROUP(mock);
}

int	main(int argc, const char *argv[])
{
	return UnityMain(argc, argv, run_all_tests);
}
