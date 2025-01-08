#include <unistd.h>
#include <stdlib.h>
#include "main.h"

/**
 *_strcpy - copies the string pointed to by src, to dest
 *@dest: the destination adress to copy the str
 *@src: the src value to copy to the new adress destination
 *Return: char return dest
 */
char *_strcpy(char *dest, char *src)
{
	int i, j = 0;

	while (src[j] != '\0')
		j++;

	for (i = 0; i <= j; i++)
		dest[i] = src[i];

	return (dest);
}

/**
 *_strlen - returns the length of a string.
 *@s: var that contain the strings character
 *Return: return the length of the string
 */
int _strlen(char *s)
{
	int a = 0;

	while (s[a] != '\0')
		a++;
	return (a);
}

/**
 *_strcmp - compare 2 different string variable
 *@s1: var that return the int
 *@s2: var to compare with the first var
 *Return: 0 if same, -1 if less, +1 if bigger
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int value = 0;
	int found_diff = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (found_diff == 0)
		{
			if (s1[i] > s2[i])
			{
				value = s1[i] - s2[i];
				found_diff++;
			}
			else if (s1[i] < s2[i])
			{
				value = s1[i] - s2[i];
				found_diff++;
			}
		}
		i++;
	}
	return (value);
}

/**
 *_strncmp - compare 2 different string variable
 *@str1: var that return the int
 *@str2: var to compare with the first var
 *@n: the number of char to compare
 *Return: int
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}

		if (str1[i] == '\0')
		{
			return (0);
		}
	}

	return (0);
}

/**
 *_strdup - duplicate a string to another malloced one
 *@s: the string to copy
 *Return: the dupplicate malloced new char *
 */
char *_strdup(char *s)
{
	char *copy = NULL;

	if (s == NULL)
	{
		return (NULL);
	}

	copy = malloc(_strlen(s) + 1);
	if (copy == NULL)
	{
		return (NULL);
	}

	_strcpy(copy, s);

	return (copy);
}
