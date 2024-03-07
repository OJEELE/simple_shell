#include "main.h"

int main(int ac, char **argv)
{
	char *prompt = "$";
	char *lineptr;
	size_t n = 0;
	size_t nchars_read;

	(void) ac;
	(void)argv;

	while(1)
	{
		printf("%s", prompt);
		nchars_read = getline(&lineptr, &n, stdin);
		if (nchars_read == -SIZE_MAX)
		{
			printf("exit success");

			return (-1);
		}
		printf("%s", lineptr);
		free(lineptr);
	}
	return (0);
}
