#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
*_strlen - returns the length of a string.
*@s: var that contain the strings character
*Return: return the length of the string
*/
size_t _strlen(char *s)
{
	size_t a = 0;

	while (s[a] != '\0')
		a++;
	return (a);
}

/**
*_strcat - concatenates two strings.
*@dest: the var destination where i concatenate the src var
*@src: the var source to append in the dest var
*Return: char return, the dest return
*/
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[i] != '\0')
		i++;
	i--;

	while (src[j] != '\0')
	{
		i++;
		dest[i] = src[j];
		j++;
	}
	return (dest);
}

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
