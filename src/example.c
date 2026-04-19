#include "test.h"

TEST(some_test)
{
	ASSERT(1 + 1 == 2, "something went wrong");

	return EXIT_SUCCESS;
}
