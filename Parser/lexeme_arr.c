#pragma warning (disable: 4996)

#include "lexeme_arr.h"
#include <stdlib.h>
#include <string.h>

void lexeme_arr_add(lexeme_t** arr, unsigned* size, unsigned* cap, lexeme_t value)
{
	if (*size == *cap)
		lexeme_arr_double(arr, size, cap);

	(*arr)[(*size)++] = value;
}

void lexeme_arr_double(lexeme_t** arr, unsigned* size, unsigned* cap)
{
	unsigned i;
	*cap *= 2;
	lexeme_t* newarr = malloc(sizeof(lexeme_t) * *cap);

	for (i = 0; i < *size; i++)
		newarr[i] = (*arr)[i];

	free(*arr);
	*arr = newarr;
}

#include <stdio.h>

lexeme_t make_lexeme(const char* name, unsigned token, unsigned line, bool rwhite)
{
	lexeme_t lx;
	strcpy(lx.name, name);
	lx.token = token;
	lx.line = line;
	lx.rwhite = rwhite;

	return lx;
}