#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "parser.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

unsigned check_var_define(parse_node_t* node, symbol_entry_t* symbol_table, unsigned symbol_table_size, unsigned* scope_parents, unsigned scope_size);

#endif