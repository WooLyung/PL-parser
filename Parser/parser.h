#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "datastc.h"

typedef struct rule {
	bool scope;
	unsigned left;
	unsigned right[20];
} rule_t;

bool parse(terminals tms, unsigned idx, token_stream stream, unsigned size, unsigned* max_line);
parse_tree make_parse_tree(token_stream stream, unsigned size);
void make_parse_tree_node(parse_node_t* node, int num, token_stream stream, unsigned size);
void make_symbol_table(parse_node_t* node, symbol_entry_t* symbol_table, unsigned* symbol_table_size, unsigned* scope_parents, unsigned* scope_size, unsigned scope);

#endif