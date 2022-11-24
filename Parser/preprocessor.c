#include "preprocessor.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "lexeme_arr.h"

scanned_stream preprocess(scanned_stream stream, unsigned* size, unsigned* cap)
{
	scanned_stream newstream = malloc(sizeof(lexeme_t));
	unsigned s = 0;
	unsigned cp = 1;
	
	bool open_str = false;
	bool open_comment = false;
	int comment_line = 0;

	for (unsigned i = 0; i < *size; i++)
	{
		const char* name = stream[i].name;
		const unsigned line = stream[i].line;
		const bool rwhite = stream[i].rwhite;

		if (strcmp(name, "\"") == 0) // string
		{
			if (comment_line == line || open_comment)
				continue;
			if (open_str)
			{
				open_str = false;
			}
			else
			{
				open_str = true;
				lexeme_arr_add(&newstream, &s, &cp, make_lexeme("\"", 0, line, rwhite));
			}
		}
		else if (strcmp(name, "/*") == 0) // open comment
		{
			if (comment_line == line || open_comment || open_str)
				continue;

			open_comment = true;
		}
		else if (strcmp(name, "*/") == 0) // close comment
		{
			if (comment_line == line || open_str)
				continue;

			if (open_comment)
			{
				open_comment = false;
			}
			else
			{
				LOG_E("preprocessor: unexpected */");
				exit(1);
			}
		}
		else if (strcmp(stream[i].name, "//") == 0) // line comment
		{
			if (comment_line == line || open_comment || open_str)
				continue;

			comment_line = line;
		}
		else
		{
			if (comment_line == line || open_comment || open_str)
				continue;

			lexeme_arr_add(&newstream, &s, &cp, make_lexeme(name, 0, line, rwhite));
		}
	}

	if (open_comment)
	{
		LOG_E("preprocessor: */ not found");
		exit(1);
	}

	if (open_str)
	{
		LOG_E("preprocessor: \" not found");
		exit(1);
	}

	*size = s;
	*cap = cp;
	free(stream);

	return newstream;
}