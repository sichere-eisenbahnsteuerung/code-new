#include <getopt.h>
#include "test_helper.h"

extern Suite *test_rs232_create_suite(void);

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

int main(int argc, char **argv)
{
	handle_arguments(argc, argv);

	if (current_test_date == NULL)
	{
		fprintf(stderr, "No test date specified! Aborting ...\n");
		exit(1);
	}

	struct test_helper *rs232test;

	/* Create all test helpers */
	rs232test = test_helper_create(test_rs232_create_suite(), strdup("rs232"));

	/* Execute all test helpers */
	test_helper_execute_all(rs232test);

	/* FIXME fetch the result from all test helpers */

	/* Free all test helpers */
	test_helper_free(rs232test);

	return 0;
}

