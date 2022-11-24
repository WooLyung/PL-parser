#include "semantic_analyzer.h"

unsigned check_var_define(parse_node_t* node, symbol_entry_t* symbol_table, unsigned symbol_table_size, unsigned* scope_parents, unsigned scope_size)
{
	if (node->rule != -1)
	{
		if (node->symbol == 2040)
		{
			node = node->childs[0];

			int idx = -1;
			for (int i = 0; i < symbol_table_size; i++)
			{
				if (strcmp(symbol_table[i].name, node->name) == 0)
					idx = i;
			}

			if (idx != -1)
			{
				int curr = node->scope;
				while (curr)
				{
					if (curr == symbol_table[idx].scope)
						return 0;
					curr = scope_parents[curr];
				}
				return node->line;
			}

			return node->line;
		}

		for (int p = 0; node->childs[p]; p++)
		{
			int line = check_var_define(node->childs[p], symbol_table, symbol_table_size, scope_parents, scope_size);
			if (line)
				return line;
		}
	}

	return 0;
}
