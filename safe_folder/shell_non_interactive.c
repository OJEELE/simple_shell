#include "main.h"

/**
 * shell_non_interactive - unix command line interpreter
 *
 * Return: void
 */
void shell_non_interactive(void)
{
	char *line;
	char **args;
	int status = -1;

	do
	{
		line = read_stream();
		args = split_line(line);
		status = execute_args(args);

		free(line);
		free(args);

		if(status >= 0)
		{
			exit(status);
		}
	}
	while (status == -1)
}

/**
 * read_stream - read a line ffrom the stream
 *
 * Return: pointer to the read line
 */
char *read_stream(void)
{
	int buffsize = 1024;
	int character, i = 0;
	char *line = malloc(sizeof(char) * buffsize);

	if (line == NULL)
	{
		fprintf(stderr, "allocation error in read_stream");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		character = getchar();
		if (character == EOF)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else if (character == '\n')
		{
			line[i] = '\0';
			return (line);
		}
		else
		{
			line[i] = character;
		}
		i++;
		if (i >= buffsize)
		{
			buffsize += buffsize;
			line = realloc(line, buffsize);
			if (line == NULL)
			{
				fprintf(stderr, "reallocation error in read_stream");
				exit(EXIT_FAILURE);
			}
		}
	}
}

	
