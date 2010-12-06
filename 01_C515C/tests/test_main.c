#include <getopt.h>
#include <test_helper.h>

char log_output_directory[200];
char *current_test_date = NULL;

void print_help()
{
	printf("test_main: Test runner for the project \"Sichere Eisenbahnsteuerung\"\n");
	printf("options:\n");
	printf("\t-t, --test-date     test date to use for log output\n");
	printf("\t-h, --help          this help output\n");
}

void handle_arguments(int argc, char **argv)
{
	static struct option long_options[] = {
		{ "test-date", 1, 0, 't' },
		{ "help", 1, 0, 'h' },
		{ NULL, 0, NULL, 0 },
	};

	int c;
	int option_index = 0;

	while ((c = getopt_long(argc, argv, "t:h", long_options, &option_index)) != -1)
	{
		switch (c) 
		{
			case 't':
				current_test_date = strdup(optarg);
				break;
			case 'h':
				print_help();
				exit(1);
			default:
				fprintf(stderr, "?? got invalid command line argument\n");
				exit(1);
		}
	}
}

extern ctest_suite *test_rs232_create_suite(void);

int main(int argc, char **argv)
{
	char buffer[200];

	handle_arguments(argc, argv);

	if (current_test_date == NULL)
	{
		fprintf(stderr, "No test date specified! Aborting ...\n");
		exit(1);
	}
	
	ctest_runner *runner = ctest_runner_create();

	ctest_runner_add_suite(runner, test_rs232_create_suite());
	
	ctest_runner_execute_all(runner);

	ctest_runner_free(runner);

	return 0;
}

