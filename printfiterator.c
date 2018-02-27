#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "holberton.h"

/**
 *printfiterator - loops through and decides which specifier to use
 *@form: the format string to be printed
 *@spec: the array of structures that identify the specifier functions
 *@args: the va_list argument list for the variadic function
 *@b: buffer to add characters to
 *
 *Return: the number of characters printed to stdout
 */
int printfiterator(const char *form, specifiers *spec, va_list args, char *b)
{
	int fi, bi = 0, si, sti = 0;
	char *str;

	for (fi = 0; form != NULL && form[fi] != '\0'; fi++)
	{
		if (form[fi] == '\\')
		{
			fi++;
			b[bi] = form[fi];
			bi++;
		}
		if (form[fi] == '%')
		{
			fi++;
			while (form[fi] == ' ' && form != '\0')
				fi++;

			if (form[fi] != ' ')
			{
				for (si = 0; spec[si].s != NULL; si++)
					if (*(spec[si].s) == form[fi])
					{
						str = (spec[si].printspec)(args);
						if (str == NULL)
							return (-1);
						for (sti = 0; str[sti] != '\0'; sti++, bi++)
							b[bi] = str[sti];
					}
			}
		}
		else
		{
			b[bi] = form[fi];
			bi++;
		}
	}
	va_end(args);
	return (bi);
}
