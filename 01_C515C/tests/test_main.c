#include <getopt.h>
#include "test_helper.h"

extern TCase *test_rs232_create(void);

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
	char buffer[200];

	handle_arguments(argc, argv);

	if (current_test_date == NULL)
	{
		fprintf(stderr, "No test date specified! Aborting ...\n");
		exit(1);
	}
	
	Suite *suite = suite_create("sichere-eisenbahnsteuerung");

	suite_add_tcase(suite, test_rs232_create());

	SRunner *runner = srunner_create(suite);

	snprintf(buffer, 200, "logs/%s_results.xml", current_test_date);
	srunner_set_xml(runner, strdup(buffer));

	srunner_run_all(runner, CK_VERBOSE);

	srunner_free(runner);

	return 0;
}

