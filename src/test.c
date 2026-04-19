#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct test_entry *tests = {};
unsigned int test_count = 0;

inline int test_register(const char *name, test_func_t func)
{
	struct test_entry *tmp
		= realloc(tests, (test_count + 1) * sizeof(*tests));
	if (!tmp) {
		return 0;
	}

	tests = tmp;
	tests[test_count].name = name;
	tests[test_count].func = func;
	test_count++;
	return 1;
}

struct test_entry *test_lookup(const char *name)
{
	for (int i = 0; i < test_count; ++i) {
		if (strcmp(name, tests[i].name) == 0) {
			return &tests[i];
		}
	}
	return NULL;
}

void *test_thread_run(void *args_)
{
	struct test_thread_args *arg = args_;

	arg->retval = arg->test();

	return EXIT_SUCCESS;
}

int test_run(int argc, char *argv[])
{
	if (argc <= 1) {
		printf("No tests provided\n");
		return EXIT_SUCCESS;
	}

	printf("Testing...\n");

	for (int a = 1; a < argc; ++a) {
		const char *requested = argv[a];
		struct test_entry *test = test_lookup(requested);

		if (test == NULL) {
			printf("Test not found: %s\n", requested);
			continue;
		}

		printf("Running test: %s\n", test->name);

		int result = test->func();

		if (result == EXIT_FAILURE) {
			printf("✕ Failed test: %s\n", test->name);
			return EXIT_FAILURE;
		}

		printf("Passed test: %s\n", test->name);
	}

	return EXIT_SUCCESS;
}
