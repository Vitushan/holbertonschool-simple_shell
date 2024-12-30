#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

/**
 * handle_builtin_commands - handle intern commands and cat
 * @argv: the arr that contain the tokenize line
 * @line: the line from the stdin
 * Return: void
 */
int handle_builtin_commands(char **argv, char *line)
{
	int i = 0;
	size_t len = 0;
	ssize_t nread;
	int is_interactive = isatty(STDIN_FILENO);

	if (is_interactive == 0)
	{
		while (argv[i] != NULL)
		{
			if (i != 0)
				printf(" ");
			printf("%s", argv[i]);
			i++;
		}
		while ((nread = getline(&line, &len, stdin)) != -1)
		{
			printf("%s", line);
		}
	}

	printf("\n");

	return (0);
}
