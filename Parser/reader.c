#include "reader.h"
#include <stdlib.h>
#include <ctype.h>
#include "logger.h"
#include "lexeme_arr.h"

scanned_stream read_file(FILE* fp, unsigned* size, unsigned* cap, char file[1024][1024])
{
	scanned_stream stream = malloc(sizeof(lexeme_t));
	unsigned s = 0;
	unsigned cp = 1;

	char c;
	char buffer[MAX_LEXEME_LEN];
	int len = 0;
	int line = 1;

	int idx = 0;

	while (c = getc(fp))
	{
		if (c == '\n' || c == EOF)
		{
			file[line][idx] = '\0';
			idx = 0;
		}
		else
		{
			file[line][idx++] = c;
		}

		if (!isspace(c) && c != EOF)
		{
			buffer[len++] = c;

			if (split_by2(buffer, len))
			{
				char tmp = buffer[len - 3];
				buffer[len - 3] = '\0';

				if (len != 3)
				{
					lexeme_arr_add(&stream, &s, &cp, make_lexeme(buffer, 0, line, false));
				}

				buffer[len - 3] = tmp;
				tmp = buffer[len - 1];
				buffer[len - 1] = '\0';
				lexeme_arr_add(&stream, &s, &cp, make_lexeme(buffer + len - 3, 0, line, false));
				buffer[0] = tmp;
				len = 1;
			}
			else if (split_by1(buffer, len))
			{
				char tmp = buffer[len - 2];
				buffer[len - 2] = '\0';

				if (len != 2)
				{
					lexeme_arr_add(&stream, &s, &cp, make_lexeme(buffer, 0, line, false));
				}

				buffer[len - 2] = tmp;
				tmp = buffer[len - 1];
				buffer[len - 1] = '\0';
				lexeme_arr_add(&stream, &s, &cp, make_lexeme(buffer + len - 2, 0, line, false));
				buffer[0] = tmp;
				len = 1;
			}
		}
		else
		{
			if (len > 1)
			{
				buffer[len++] = '\0';
				if (split_by1(buffer, len))
				{
					char tmp = buffer[len - 2];
					buffer[len - 2] = '\0';
					lexeme_arr_add(&stream, &s, &cp, make_lexeme(buffer, 0, line, false));
					buffer[len - 2] = tmp;
					lexeme_arr_add(&stream, &s, &cp, make_lexeme(buffer + len - 2, 0, line, true));
					len = 0;
				}
				else
				{
					lexeme_arr_add(&stream, &s, &cp, make_lexeme(buffer, 0, line, true));
					len = 0;
				}
			}
			else if (len != 0)
			{
				buffer[len] = '\0';
				lexeme_arr_add(&stream, &s, &cp, make_lexeme(buffer, 0, line, true));
				len = 0;
			}
		}

		if (c == EOF)
			break;
		if (c == '\n')
			line++;
	}

	*size = s;
	*cap = cp;
	return stream;
}

bool split_by1(const char* buffer, unsigned len)
{
	if (len < 2)
		return false;

	if (buffer[len - 2] == ':')
		return true;
	if (buffer[len - 2] == '"')
		return true;
	if (buffer[len - 2] == '+')
		return true;
	if (buffer[len - 2] == '-')
		return true;
	if (buffer[len - 2] == '%')
		return true;
	if (buffer[len - 2] == '{')
		return true;
	if (buffer[len - 2] == '}')
		return true;
	if (buffer[len - 2] == ';')
		return true;
	if (buffer[len - 2] == ',')
		return true;
	if (buffer[len - 2] == '.')
		return true;
	if (buffer[len - 2] == '(')
		return true;
	if (buffer[len - 2] == ')')
		return true;
	if (buffer[len - 2] == '*' && buffer[len - 1] != '/' && (len == 2 || buffer[len - 3] != '/'))
		return true;
	if (buffer[len - 2] == '/' && buffer[len - 1] != '*' && (len == 2 || buffer[len - 3] != '*')
		&& buffer[len - 1] != '/' && (len != 2 && buffer[len - 3] != '/'))
		return true;
	if (buffer[len - 2] == '<' && buffer[len - 1] != '=')
		return true;
	if (buffer[len - 2] == '>' && buffer[len - 1] != '=')
		return true;
	if (buffer[len - 2] == '!' && buffer[len - 1] != '=')
		return true;	
	if (buffer[len - 2] == '=' && buffer[len - 1] != '=' && (len == 2 
		|| (buffer[len - 3] != '=' && buffer[len - 3] != '>' && buffer[len - 3] != '<' && buffer[len - 3] != '!')))
		return true;	
	if (buffer[len - 2] == '[' && buffer[len - 1] != ']')
		return true;
	if (buffer[len - 2] == ']' && (len == 2 || buffer[len - 3] != '['))
		return true;

	return false;
}

bool split_by2(const char* buffer, unsigned len)
{
	if (len < 3)
		return false;

	if (buffer[len - 2] == '=' && buffer[len - 3] == '<')
		return true;
	if (buffer[len - 2] == '=' && buffer[len - 3] == '>')
		return true;
	if (buffer[len - 2] == '=' && buffer[len - 3] == '=')
		return true;
	if (buffer[len - 2] == '=' && buffer[len - 3] == '!')
		return true;
	if (buffer[len - 2] == '&' && buffer[len - 3] == '&')
		return true;
	if (buffer[len - 2] == '|' && buffer[len - 3] == '|')
		return true;
	if (buffer[len - 2] == '[' && buffer[len - 3] == ']')
		return true;
	if (buffer[len - 2] == '*' && buffer[len - 3] == '/')
		return true;
	if (buffer[len - 2] == '/' && buffer[len - 3] == '*')
		return true;
	if (buffer[len - 2] == '/' && buffer[len - 3] == '/')
		return true;

	return false;
}