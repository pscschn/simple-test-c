# Simple Tests in C

Maybe the simplest test kit you'll find.

Example: 

```c
#include "test.h"

TEST(some_test)
{
	ASSERT(1 + 1 == 2, "something went wrong");

	return EXIT_SUCCESS;
}

```

```c
#include "test.h"

int some_func();

TEST(test_run_some_thread)
{
	pthread_t tt;

	struct test_thread_args *tt_args
		= &TEST_THREAD_ARGS(some_func);

	pthread_create(&tt, NULL, test_thread_run, tt_args);

	pthread_join(tt, NULL);

	ASSERT((tt_args->retval) == EXIT_SUCCESS, 
        "failed to run thread");

	return EXIT_SUCCESS;
}

```

```shell
./test some_test some_other_test
Testing...
Running test: some_test
Passed test: some_test
Running test: some_other_test
Passed test: some_other_test
```
