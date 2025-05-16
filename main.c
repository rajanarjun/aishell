#include <stdio.h>
#include <string.h>

void writeTempFile(char* command) {
    FILE *file = fopen(".cmd_hist.log", "a");
    if (file) {
        fprintf(file, "%s\n", command);
        fclose(file);
    }
}

void startRec(char* macro_name)
{
	char input[1024];

	while (1) {
		printf("%s >> ", macro_name);
		fflush(stdout);

		if (fgets(input, sizeof(input), stdin) == NULL) {
			printf("\n");
            break;
        }

        size_t i = strcspn(input, "\n");
        input[i] = '\0';

		if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            break;
        }

		writeTempFile(input);
        memset(input, 0, sizeof(input));
	}
}

int main(int argc, char* argv[]) {
	if (argc > 2) {
		fprintf(stderr, "Too many arguments, Usage: [%s] [macro name]\n", argv[0]);
		return 1;
	}

	char* macro_name;
	if (argc == 1) {
		macro_name = "1";
	} else if (argc == 2) {
		macro_name = argv[1];
	}

	startRec(macro_name);

	return 0;
}
