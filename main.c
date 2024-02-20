#include "main.h"
/**
 * main -  function that checks if our shell is called
 *
 * Return: 0 on success
 */
int main(void)
{
	if (issatty(STDIN_FILENO) == 1)
	{
		shell_interactive();
	}
	else
	{
		shell_non_interactive();
	}
	return (0);
}

/* shell interactive mode */

/**shell_interactive - UNIX command line interpreter
 *
 * Return: void
 */
void shell_interactive(void)
{
	char *lineptr;
	char **args;
	int status = -1;

	do {
		printf("$");
		lineptr = read_line();
		args = split_line(lineptr);
		status = execute_args(args);

		free(lineptr);
		free(args);

		if(status >= 0)
		{
			exit(status);
		}
	}
	while (status == -1);
}

/*function reads line */

#include "main.h"
/**
 * read_line - read a sline from stdin
 *
 * Return: pointer that points to a string with the line content
 */
char *read_line(void)
{
	char *line = NULL;
	size_t buffsize = 0;

	if (getline(&line, &buffsize, stdin) == -1)
	{
		if(feof(stdin))
		{
			free(line);
			exit(EXIT_SUCCES);
		}
		else
		{
			free(line);
			perror("error reading from the stdin");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}

/* split string into multiple elements */
/**
 * split_line -  split a string into multiple strings
 * @line: string to be splitted
 *
 * Return: pointer to the new arrray
 */
char **split_line(char *line)
{
	int buffsize = 64;
	int i = 0;
	char **tokens = malloc(buffsize * sizeof(char *));
	char *token;
	char delim = " \t\n";

	if (!tokens)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, delim);
	while (token != NULL)
	{

