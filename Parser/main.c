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

#define MAX_FILE_NAME_LEN 64

char file[1024][1024];

int main()
{
	// variables
	char fileName[MAX_FILE_NAME_LEN];
	FILE* fp;
	unsigned size;
	unsigned cap;

	// intermediate results
	scanned_stream scan_s;
	token_stream token_s;
	terminal_t tms[1024];
	unsigned max_line = 0;

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
		make_parse_tree(token_s, size);
	}

	//printf("%d, %d\n", result, max_line);
	//for (unsigned i = 0; i < size; i++)
	//	printf("%d ", token_s[i].token);
	//printf("\n");

	// semantic analyzer

	return 0;
}