# Simple Tests in C

Minimal C test kit for defining unit tests.
Define tests with simple macros and run individual tests by passing the test function name to the binary.
DAP-friendly — works well with nvim-dap and other Debug Adapter Protocol clients.

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
