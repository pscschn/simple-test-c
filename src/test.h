
#define TEST_REGISTER(ptr)                                                     \
	__attribute__((unused));                                               \
	__attribute__((constructor)) static void register_##ptr(void)          \
	{                                                                      \
		test_register(#ptr, ptr);                                      \
	}

#define TEST(f)                                                                \
	int f();                                                               \
	TEST_REGISTER(f)                                                       \
	int f()

#define ASSERT(statement, msg, ...)                                            \
	do {                                                                   \
		if (!(statement)) {                                            \
			printf(msg, ##__VA_ARGS__);                            \
			printf("\n");                                          \
			return EXIT_FAILURE;                                   \
		}                                                              \
	} while (0);

#define TEST_THREAD_ARGS(test) (struct test_thread_args){ 0, (test) };


typedef int (*test_func_t)();

struct test_entry
{
	const char *name;
	test_func_t func;
};

struct test_thread_args
{
	int retval;
	int (*test)();
};

extern struct test_entry *tests;

extern unsigned int test_count;

/**
 * @brief Adds a function to the array of tests
 *	The function pointer can be identified in the array by the provided name
 */
int test_register(const char *name, test_func_t func);

/**
 * @brief Returns the first occurence of a test entry by name
 */
struct test_entry *test_lookup(const char *name);

void *test_thread_run(void *args_);

/**
 * @brief Executes registered tests by their registered name
 *
 * Searches for a registered test for each name provided in argv.
 * If no names are provided then it falls back to default arguments
 */
int test_run(int argc, char *argv[]);
