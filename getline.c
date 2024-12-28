#include <stdio.h>

int main(void)
{
	ssize_t char_read = 0;
	char *line = NULL;
	size_t buff_len = 0;

	printf("$ ");
	char_read = getline(&line, &buff_len, stdin);
	if (char_read == -1)
		printf("EOF\n");
	else
		printf("buff_len = %zu\n", buff_len);
		printf("%s", line);
	return (0);
}
