#include "main.h"
/**
 * main -  function that checks if our shell is called
 *
 * Return: 0 on success
 */
int main(void)
{
	if (isatty(STDIN_FILENO) == 1)
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
			exit(EXIT_SUCCESS);
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
	char *delim = " \t\n\r\a\"";

	if (!tokens)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, delim);
	while (token != NULL)
	{
		if (token[0] == '#')
		{
			break;
		}
		tokens[i] = token;
		i++;
		if (i >= buffsize)
		{
			buffsize += buffsize;
			tokens = realloc(tokens, buffsize * sizeof (char *));
			if (!tokens)
			{
				fprintf(stderr, "reallocation failure");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delim);
	}
		tokens[i] = NULL;
		return (tokens);
}
/* execute the command line or process */

/**
 * execute_args - map if command is a bultin or a process 
 * @args: command and its flags
 *
 * Return: 1 on success or 0 otherwise
 */
int execute_args(char **args)
{
	char *builtin_commands[] = {
		"cd",
		"env",
		"help",
		"exit"
	};
	int (*builtin_functions[])(char **) = {
		&own_cd,
		&own_env,
		&own_help,
		&own_exit
	};
	size_t i = 0;
	size_t num_builtins = sizeof(builtin_commands) / sizeof(builtin_commands[0]);
	if (args[0] == NULL)
	{
		fprintf(stderr, "No command provided.\n");
		return (-1);
	}

	for (; i < num_builtins; i++)
	{
		if (strcmp(args[0], builtin_commands[i]) == 0)
		{
			return ((*builtin_functions[i])(args));
		}
	}
	return (new_process(args));
}
			
