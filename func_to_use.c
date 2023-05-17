#include "shell.h"

/**
* size_of - gives the value of a string
* @str: string to be misured
* @spaces: 0 if str length and 1 if spaces length
* Return: size of a string
*/
size_t size_of(char *str, size_t spaces)
{
	size_t i = 0;

	if (spaces == 0)
	{
		while (*str++)
		{
			i++;
		}
	}
	else
	{
		while (*str)
		{
			if (*str == ' ')
			{
				i++;
			}
			str++;
		}
		i += 2;
	}
	return (i);
}

/**
* _strcpy - copies the string pointed to by src
* @dest: pointer to the buffer in which we copy the string
* @src: string to be copied
* Return: the pointer to dest
*/
char *_strcpy(char *dest, const char *src)
{
	int i;

	for (i = 0; src[i]; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

/**
* _free_array - frees an array of strings
* @arr: array to free
* Return: nothing
*/
void _free_array(char **arr)
{
	int i;

	if (arr == NULL)
		return;
	for (i = 0; arr[i] != NULL; i++)
	{
		free(arr[i]);
	}
	free(arr);
}
