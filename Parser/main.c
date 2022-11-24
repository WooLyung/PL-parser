#pragma warning (disable: 4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "logger.h"
#include "datastc.h"
#include "reader.h"
#include "preprocessor.h"
#include "lexer.h"
#include "parser.h"
#include "semantic_analyzer.h"

#define MAX_FILE_NAME_LEN 64

char file[1024][1024];

// intermediate results
scanned_stream scan_s;
token_stream token_s;
terminal_t tms[1024];
parse_tree root;

symbol_entry_t symbol_table[1024];
unsigned scope_parents[1024];
unsigned symbol_table_size = 0;
unsigned scope_size = 0;

unsigned max_line = 0;

int main()
{
	// variables
	char fileName[MAX_FILE_NAME_LEN];
	FILE* fp;
	unsigned size;
	unsigned cap;

	// input file name
	printf("source file name: ");
	scanf("%s", fileName);

	fp = fopen(fileName, "r");
	if (!fp)
	{
		LOG_E("file open failed");
		return 1;
	}

	// reader
	LOG_I("execute reader .......................");
	scan_s = read_file(fp, &size, &cap, file);
	LOG_I("finish reader ........................");

	// preprocessor
	LOG_I("execute preprocessor .................");
	scan_s = preprocess(scan_s, &size, &cap);
	LOG_I("finish preprocessor ..................");

	// lexer
	LOG_I("execute lexer ........................");
	token_s = lexical_analysis(scan_s, &size, &cap);
	if (complete_lexer(token_s, size, file))
	{
		LOG_I("finish lexer .........................");
	}
	else
		return 1;

	// parser
	LOG_I("execute parser .......................");

	for (int i = 0; i < 1024; i++)
	{
		tms[i].token = -1;
		tms[i].d_by = -1;
	}
	tms[0].token = 2001;
	tms[0].d_by = 0;

	bool result = parse(tms, 0, token_s, size, &max_line);
	if (!result)
	{
		LOG_E("parser error: error line %d", max_line);
		LOG_E("%s", file[max_line]);
		LOG_E("");
		exit(1);
	}
	else
	{
		for (int i = 0; i < 1024; i++)
			scope_parents[i] = 0;
		scope_size = 1;

		root = make_parse_tree(token_s, size);
		make_symbol_table(root, symbol_table, &symbol_table_size, scope_parents, &scope_size, 0, file);
	}
	LOG_I("finish parser ........................");

	// semantic analyzer
	LOG_I("execute semantic analyzer ............");
	int err_line = check_var_define(root, symbol_table, symbol_table_size, scope_parents, scope_size);
	if (err_line)
	{
		LOG_E("undefined variable error: error line %d", err_line);
		LOG_E("%s", file[err_line]);
		LOG_E("");

		exit(1);
	}
	else
		LOG_I("finish semantic analyzer .............");

	LOG_I("");
	LOG_I("compilation success");

	return 0;
}