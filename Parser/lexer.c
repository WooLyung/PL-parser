#pragma warning (disable: 4996)

#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "logger.h"
#include "lexeme_arr.h"

#define COMP_NAME(x,n) if(strcmp(name, x) == 0) return n;

bool complete_lexer(token_stream stream, unsigned size, char file[1024][1024])
{
	bool complete = true;
	unsigned line = 0;

	for (unsigned i = 0; i < size; i++)
	{
		if (stream[i].token == 0 && line != stream[i].line)
		{
			line = stream[i].line;
			LOG_E("lexer error: error line %d", line);
			LOG_E("%s", file[line]);
			LOG_E("");
			complete = false;
		}
	}
	
	return complete;
}

token_stream lexical_analysis(scanned_stream stream, unsigned* size, unsigned* cap)
{
	scanned_stream newstream = malloc(sizeof(lexeme_t));
	unsigned s = 0;
	unsigned cp = 1;

	for (unsigned i = 0; i < *size; i++)
	{
		const char* name = stream[i].name;
		const unsigned line = stream[i].line;
		const bool rwhite = stream[i].rwhite;
		unsigned code = 0;

		code = check_double(stream, *size, i);
		if (code)
		{

			lexeme_t lx = make_lexeme(name, 3, line, stream[i + code - 1].rwhite);
			for (unsigned j = 1; j < code; j++)
				strcat(lx.name, stream[i + j].name);
			lexeme_arr_add(&newstream, &s, &cp, lx);
			i += code - 1;

			continue;
		}

		code = check_integer(stream, *size, i);
		if (code)
		{
			lexeme_t lx = make_lexeme(name, 2, line, stream[i + code - 1].rwhite);
			for (unsigned j = 1; j < code; j++)
				strcat(lx.name, stream[i + j].name);
			lexeme_arr_add(&newstream, &s, &cp, lx);
			i += code - 1;

			continue;
		}
		
		code = check_keyword(name);
		if (code)
		{
			lexeme_arr_add(&newstream, &s, &cp, make_lexeme(name, code, line, rwhite));
			continue;
		}

		code = check_identifier(name);
		if (code)
		{
			lexeme_arr_add(&newstream, &s, &cp, make_lexeme(name, code, line, rwhite));
			continue;
		}

		code = check_sign(name);

		if (code)
		{
			lexeme_arr_add(&newstream, &s, &cp, make_lexeme(name, code, line, rwhite));
			continue;
		}

		if (strcmp(name, "\"") == 0)
		{
			lexeme_arr_add(&newstream, &s, &cp, make_lexeme(name, 54, line, rwhite));
			continue;
		}

		if (strcmp(name, "true") == 0 || strcmp(name, "false") == 0)
		{
			lexeme_arr_add(&newstream, &s, &cp, make_lexeme(name, 55, line, rwhite));
			continue;
		}

		lexeme_arr_add(&newstream, &s, &cp, make_lexeme(name, 0, line, rwhite));
	}

	*size = s;
	*cap = cp;

	return newstream;
}

unsigned check_keyword(const char* name)
{
	COMP_NAME("int", 29);
	COMP_NAME("double", 30);
	COMP_NAME("bool", 31);
	COMP_NAME("string", 32);
	COMP_NAME("void", 33);
	COMP_NAME("break", 34);
	COMP_NAME("class", 35);
	COMP_NAME("else", 36);
	COMP_NAME("extends", 37);
	COMP_NAME("for", 38);
	COMP_NAME("if", 39);
	COMP_NAME("new", 40);
	COMP_NAME("null", 41);
	COMP_NAME("return", 42);
	COMP_NAME("this", 43);
	COMP_NAME("while", 44);
	COMP_NAME("static", 45);
	COMP_NAME("Print", 46);
	COMP_NAME("instanceof", 47);
	COMP_NAME("NewArray", 48);
	COMP_NAME("implements", 49);
	COMP_NAME("interface", 50);
	COMP_NAME("switch", 51);
	COMP_NAME("case", 52);
	COMP_NAME("default", 53);

	return 0;
}

unsigned check_sign(const char* name)
{
	COMP_NAME("+", 4);
	COMP_NAME("-", 5);
	COMP_NAME("*", 6);
	COMP_NAME("/", 7);
	COMP_NAME("%", 8);
	COMP_NAME("<", 9);
	COMP_NAME("<=", 10);
	COMP_NAME(">", 11);
	COMP_NAME(">=", 12);
	COMP_NAME("=", 13);
	COMP_NAME("==", 14);
	COMP_NAME("!=", 15);
	COMP_NAME("&&", 16);
	COMP_NAME("||", 17);
	COMP_NAME("!", 18);
	COMP_NAME(";", 19);
	COMP_NAME(",", 20);
	COMP_NAME(".", 21);
	COMP_NAME("[", 22);
	COMP_NAME("]", 23);
	COMP_NAME("(", 24);
	COMP_NAME(")", 25);
	COMP_NAME("{", 26);
	COMP_NAME("}", 27);
	COMP_NAME("[]", 28);
	COMP_NAME(":", 56);

	return 0;
}

unsigned check_identifier(const char* name) // [a-zA-Z_]+[a-zA-Z0-9_]*
{
	unsigned i;
	const char* iter;

	for (i = 0, iter = name; *iter; iter++, i++)
	{
		char c = *iter;
		if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_')
			continue;
		if (i != 0 && ('0' <= c && c <= '9'))
			continue;

		return 0;
	}

	return 1;
}

bool check_int(const char* name) // [0-9]+
{
	size_t len = strlen(name);
	unsigned i;

	for (i = 0; i < len; i++)
	{
		if (name[i] < '0' || name[i] > '9')
			return false;
	}

	return true;
}

bool check_int_e(const char* name) // [0-9]+[eE]
{
	size_t len = strlen(name);
	unsigned i;

	if (len < 2)
		return false;

	for (i = 0; i < len - 1; i++)
	{
		if (name[i] < '0' || name[i] > '9')
			return false;
	}

	if (name[len - 1] == 'e' || name[len - 1] == 'E')
		return true;

	return false;
}

bool check_e_int(const char* name) // [eE][0-9]+
{
	size_t len = strlen(name);
	unsigned i;

	if (len < 2)
		return false;

	for (i = 1; i < len; i++)
	{
		if (name[i] < '0' || name[i] > '9')
			return false;
	}

	if (name[0] == 'e' || name[0] == 'E')
		return true;

	return false;
}

bool check_int_e_int(const char* name) // [0-9]+[eE][0-9]+
{
	size_t len = strlen(name);
	unsigned i;
	unsigned e = -1;

	if (len < 3)
		return false;

	for (i = 1; i < len - 1; i++)
	{
		if (name[i] == 'e' || name[i] == 'E')
		{
			if (e != -1)
				return false;

			e = i;
		}
	}

	for (i = 0; i < len; i++)
	{
		if ((name[i] < '0' || name[i] > '9') && e != i)
			return false;
	}

	return true;
}

unsigned get_num_part(const char* name)
{
	if (check_int(name))
		return 1001;
	if (check_int_e(name))
		return 1002;
	if (check_e_int(name))
		return 1003;
	if (check_int_e_int(name))
		return 1004;
	if (strcmp(name, ".") == 0)
		return 1005;
	if (strcmp(name, "+") == 0 || strcmp(name, "-") == 0)
		return 1006;
	if (strcmp(name, "e") == 0 || strcmp(name, "E") == 0)
		return 1007;
	return 0;
}

unsigned check_integer(scanned_stream stream, unsigned size, unsigned i)
{
	if (size - i >= 3 && !stream[i + 0].rwhite && !stream[i + 1].rwhite)
	{
		unsigned p0 = get_num_part(stream[i + 0].name);
		unsigned p1 = get_num_part(stream[i + 1].name);
		unsigned p2 = get_num_part(stream[i + 2].name);

		if (p0 == 1002 && p1 == 1006 && p2 == 1001)
			return 3;
	}

	if (size - i >= 2 && !stream[i + 0].rwhite)
	{
		unsigned p0 = get_num_part(stream[i + 0].name);
		unsigned p1 = get_num_part(stream[i + 1].name);

		if (p0 == 1002 && p1 == 1001)
			return 2;
	}

	if (size - i >= 1)
	{
		unsigned p0 = get_num_part(stream[i + 0].name);

		if (p0 == 1001)
			return 1;

		if (p0 == 1004)
			return 1;
	}

	return 0;
}

unsigned check_double(scanned_stream stream, unsigned size, unsigned i)
{
	if (size - i >= 5 && !stream[i + 0].rwhite && !stream[i + 1].rwhite && !stream[i + 2].rwhite && !stream[i + 3].rwhite)
	{
		unsigned p0 = get_num_part(stream[i + 0].name);
		unsigned p1 = get_num_part(stream[i + 1].name);
		unsigned p2 = get_num_part(stream[i + 2].name);
		unsigned p3 = get_num_part(stream[i + 3].name);
		unsigned p4 = get_num_part(stream[i + 4].name);

		if (p0 == 1001 && p1 == 1005 && p2 == 1002 && p3 == 1006 && p4 == 1001)
			return 5;

		if (p0 == 1001 && p1 == 1005 && p2 == 1007 && p3 == 1006 && p4 == 1001)
			return 5;
	}

	if (size - i >= 4 && !stream[i + 0].rwhite && !stream[i + 1].rwhite && !stream[i + 2].rwhite)
	{
		unsigned p0 = get_num_part(stream[i + 0].name);
		unsigned p1 = get_num_part(stream[i + 1].name);
		unsigned p2 = get_num_part(stream[i + 2].name);
		unsigned p3 = get_num_part(stream[i + 3].name);

		if (p0 == 1005 && p1 == 1002 && p2 == 1006 && p3 == 1001)
			return 4;
	}

	if (size - i >= 3 && !stream[i + 0].rwhite && !stream[i + 1].rwhite)
	{
		unsigned p0 = get_num_part(stream[i + 0].name);
		unsigned p1 = get_num_part(stream[i + 1].name);
		unsigned p2 = get_num_part(stream[i + 2].name);

		if (p0 == 1001 && p1 == 1005 && p2 == 1001)
			return 3;

		if (p0 == 1001 && p1 == 1005 && p2 == 1004)
			return 3;
	}

	if (size - i >= 2 && !stream[i + 0].rwhite)
	{
		unsigned p0 = get_num_part(stream[i + 0].name);
		unsigned p1 = get_num_part(stream[i + 1].name);

		if (p0 == 1001 && p1 == 1005)
			return 2;

		if (p0 == 1005 && p1 == 1001)
			return 2;

		if (p0 == 1005 && p1 == 1004)
			return 2;
	}

	return 0;
}