#include "main.h"

/**
 * new_process - create a new process
 * @args: array of strings that contains the mamand and its flags
 *
 * Return: 1 if success, 0 otherwise
 */

int new_process(char **args)
{
	pid_t pid;
	int status;

	pid =fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("error in new process:child process");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror(" error in new process: forking");
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (-1);
}

/**
 * own_env - function executes builtin environment command
 *
 * Return: 1 on sucess
 */
int own_env(char **args)
{
	printf("Executing own_env command\n");
	return (1);
}
/**
 * own_cd - execute cd builtin command
 *
 *
 */
int own_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "cd: missing argument\n");
	}
	else
	{
		if(chdir(args[1]) != 0)
			perror("cd");
	}
	return (1);
}

int own_exit(char **args)
{
	printf("EXecuting own_exit command\n");
	exit(EXIT_SUCCESS);
}

int own_help(char **args)
{
	printf("executing own_help command\n");
	return (1);
}
