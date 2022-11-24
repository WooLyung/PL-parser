#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "datastc.h"

typedef struct rule {
	bool scope;
	unsigned left;
	unsigned right[20];
} rule_t;

bool parse(terminals tms, unsigned idx, token_stream stream, unsigned size,
	unsigned* max_line);
void make_parse_tree(token_stream stream, unsigned size);
void make_parse_tree_node(parse_node_t* node, int num, token_stream stream, unsigned size);

#endif