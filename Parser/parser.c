#pragma warning (disable: 4996)

#include "parser.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

rule_t rules[] = {
	{ false, 2001, { 2002, 0 } },
	{ false, 2002, { 2003, 0 } },
	{ false, 2002, { 2003, 2002, 0 } },
	{ false, 2003, { 2004, 0 } },
	{ false, 2003, { 2007, 0 } },
	{ false, 2003, { 2010, 0 } },
	{ false, 2003, { 2016, 0 } },
	{ false, 2004, { 2005, 19, 0 } },
	{ false, 2005, { 2006, 1, 0 } },
	{ false, 2006, { 29, 0 } },
	{ false, 2006, { 30, 0 } },
	{ false, 2006, { 31, 0 } },
	{ false, 2006, { 32, 0 } },
	{ false, 2006, { 1, 0 } },
	{ false, 2006, { 2006, 28, 0 } },
	{ false, 2007, { 33, 1, 24, 25, 2019, 0 } },
	{ false, 2007, { 2006, 1, 24, 25, 2019, 0 } },
	{ false, 2007, { 2006, 1, 24, 2008, 25, 2019, 0 } },
	{ false, 2007, { 33, 1, 24, 2008, 25, 2019, 0 } },
	{ false, 2008, { 2005, 0 } },
	{ false, 2008, { 2005, 20, 2008, 0 } },
	{ false, 2010, { 35, 1, 26, 27, 0 } },
	{ false, 2010, { 35, 1, 49, 2012, 26, 27, 0 } },
	{ false, 2010, { 35, 1, 37, 1, 26, 27, 0 } },
	{ false, 2010, { 35, 1, 37, 1, 49, 2012, 26, 27, 0 } },
	{ false, 2010, { 35, 1, 26, 2014, 27, 0 } },
	{ false, 2010, { 35, 1, 37, 1, 26, 2014, 27, 0 } },
	{ false, 2010, { 35, 1, 49, 2012, 26, 2014, 27, 0 } },
	{ false, 2010, { 35, 1, 37, 1, 49, 2012, 26, 2014, 27, 0 } },
	{ false, 2012, { 1, 0 } },
	{ false, 2012, { 1, 20, 2012, 0 } },
	{ false, 2014, { 2015, 0 } },
	{ false, 2014, { 2015, 2014, 0 } },
	{ false, 2015, { 2004, 0 } },
	{ false, 2015, { 2007, 0 } },
	{ false, 2016, { 50, 1, 26, 2017, 27, 0 } },
	{ false, 2016, { 50, 1, 26, 27, 0 } },
	{ false, 2017, { 2018, 0 } },
	{ false, 2017, { 2018, 2017, 0 } },
	{ false, 2018, { 33, 1, 24, 25, 19, 0 } },
	{ false, 2018, { 2006, 1, 24, 25, 19, 0 } },
	{ false, 2018, { 33, 1, 24, 2008, 25, 19, 0 } },
	{ false, 2018, { 2006, 1, 24, 2008, 25, 19, 0 } },
	{ false, 2019, { 26, 27, 0 } },
	{ false, 2019, { 26, 2020, 27, 0 } },
	{ false, 2019, { 26, 2021, 27, 0 } },
	{ false, 2019, { 26, 2020, 2021, 27, 0 } },
	{ false, 2020, { 2004, 0 } },
	{ false, 2020, { 2004, 2020, 0 } },
	{ false, 2021, { 2022, 0 } },
	{ false, 2021, { 2022, 2021, 0 } },
	{ false, 2022, { 2034, 19, 0 } },
	{ false, 2022, { 2023, 0 } },
	{ false, 2022, { 2024, 0 } },
	{ false, 2022, { 2025, 0 } },
	{ false, 2022, { 2026, 0 } },
	{ false, 2022, { 2027, 0 } },
	{ false, 2022, { 2028, 0 } },
	{ false, 2022, { 2019, 0 } },
	{ false, 2022, { 2030, 0 } },
	{ false, 2023, { 39, 24, 2034, 25, 2022, 36, 2022, 0 } },
	{ false, 2024, { 44, 24, 2034, 25, 2022, 0 } },
	{ false, 2025, { 38, 24, 2034, 19, 2034, 19, 2034, 25, 2022, 0 } },
	{ false, 2026, { 42, 2034, 19, 0 } },
	{ false, 2027, { 34, 19, 0 } },
	{ false, 2028, { 46, 24, 2029, 25, 19, 0 } },
	{ false, 2030, { 51, 24, 2034, 25, 26, 2031, 27, 0 } },
	{ false, 2030, { 51, 24, 2034, 25, 26, 2031, 2033, 27, 0 } },
	{ false, 2031, { 2032, 0 } },
	{ false, 2031, { 2032, 2031, 0 } },
	{ false, 2032, { 52, 56, 0 } },
	{ false, 2032, { 52, 56, 2021, 0 } },
	{ false, 2033, { 53, 56, 0  } },
	{ false, 2033, { 53, 56, 2021, 0 } },
	{ false, 2029, { 2034, 0 } },
	{ false, 2029, { 2034, 20, 2029, 0 } },
	{ false, 2034, { 2039, 0 } },
	{ false, 2039, { 2040, 0 } },
	{ false, 2039, { 2040, 13, 2034, 0 } },
	{ false, 2039, { 2038, 0 } },
	{ false, 2039, { 43, 0 } },
	{ false, 2039, { 1, 24, 25, 0 } },
	{ false, 2039, { 1, 24, 2037, 25, 0 } },
	{ false, 2039, { 24, 2034, 25, 0 } },
	{ false, 2039, { 5, 2034, 0 } },
	{ false, 2039, { 4, 2034, 0 } },
	{ false, 2039, { 18, 2034, 0 } },
	{ false, 2039, { 40, 1, 0 } },
	{ false, 2039, { 48, 24, 2034, 20, 2006, 25, 0 } },
	{ false, 2034, { 2039, 4, 2034, 0 } },
	{ false, 2034, { 2039, 5, 2034, 0 } },
	{ false, 2034, { 2039, 6, 2034, 0 } },
	{ false, 2034, { 2039, 7, 2034, 0 } },
	{ false, 2034, { 2039, 8, 2034, 0 } },
	{ false, 2034, { 2039, 9, 2034, 0 } },
	{ false, 2034, { 2039, 10, 2034, 0 } },
	{ false, 2034, { 2039, 11, 2034, 0 } },
	{ false, 2034, { 2039, 12, 2034, 0 } },
	{ false, 2034, { 2039, 14, 2034, 0 } },
	{ false, 2034, { 2039, 15, 2034, 0 } },
	{ false, 2034, { 2039, 16, 2034, 0 } },
	{ false, 2034, { 2039, 17, 2034, 0 } },
	{ false, 2037, { 2029, 20, 0 } },
	{ false, 2038, { 2, 0 } },
	{ false, 2038, { 3, 0 } },
	{ false, 2038, { 55, 0 } },
	{ false, 2038, { 54, 0 } },
	{ false, 2038, { 41, 0 } },
	{ false, 2040, { 1, 0 } }
};

int d_by[1024] = { 0, };
int d_by_rule[1024] = { 0, };
int end_point = 0;

bool parse(terminals tms, unsigned idx, token_stream stream, unsigned size, unsigned* max_line)
{
	static int curr = -1;
	curr++;
	unsigned i = idx;

	while (true)
	{
		if (i == size)
		{
			if (tms[i].token == -1)
			{
				end_point = curr;
				curr--;
				return true;
			}
			else
			{
				curr--;
				return false;
			}
		}

		if (tms[i].token > 2000)
		{
			for (int r = 0; r < 109; r++)
			{
				if (rules[r].left == tms[i].token)
				{
					unsigned max = 0;
					for (int j = 0; j < 1024; j++)
					{
						if (tms[j].d_by != -1)
							max = j;
					}

					unsigned scale = 0;
					while (rules[r].right[scale])
						scale++;
					max += scale - 1;

					if (max > 1024)
						max = 1023;

					if (max > size)
						continue;

					terminal_t tmp = tms[i];
					d_by[curr] = tms[i].d_by;
					d_by_rule[curr] = r;

					for (unsigned j = 1024 - scale; j > i; j--)
					{
						tms[j + scale - 1].token = tms[j].token;
						tms[j + scale - 1].d_by = tms[j].d_by;
					}

					for (unsigned j = 0; j < scale; j++)
					{
						tms[i + j].token = rules[r].right[j];
						tms[i + j].d_by = curr;
					}

					bool result = parse(tms, i, stream, size, max_line);

					for (unsigned j = i + 1; j < 1024; j++)
					{
						if (j + scale - 1 < 1024)
						{
							tms[j].token = tms[j + scale - 1].token;
							tms[j].d_by = tms[j + scale - 1].d_by;
						}
						else
						{
							tms[j].token = -1;
							tms[j].d_by = -1;
						}
					}

					tms[i] = tmp;

					if (result)
					{
						curr--;
						return true;
					}
				}
			}

			curr--;
			return false;
		}
		else
		{
			if (tms[i].token != stream[i].token)
			{
				curr--;
				return false;
			}

			if (stream[i].line > *max_line)
				*max_line = stream[i].line;
			i++;
		}
	}

	i++;
	return false;
}

int childs[1024][1024] = { 0, };
int idx = 0;

void make_symbol_table(parse_node_t* node, symbol_entry_t* symbol_table, unsigned* symbol_table_size, unsigned* scope_parents, unsigned* scope_size, unsigned scope, char file[1024][1024])
{
	node->scope = scope;

	if (node->rule != -1)
	{
		// in scope
		if (node->symbol == 2001 || node->symbol == 2010 || node->symbol == 2019 || node->symbol == 2007)
		{
			unsigned nscope = *scope_size;
			scope_parents[nscope] = scope;
			(*scope_size)++;

			for (int p = 0; node->childs[p]; p++)
				make_symbol_table(node->childs[p], symbol_table, symbol_table_size, scope_parents, scope_size, nscope, file);
		}
		else
		{
			if (node->symbol == 2005)
			{
				for (int i = 0; i < *symbol_table_size; i++)
				{
					if (strcmp(symbol_table[i].name, node->childs[1]->name) == 0)
					{
						LOG_E("duplicated variable error: error line %d", node->childs[1]->line);
						LOG_E("%s", file[node->childs[1]->line]);
						LOG_E("");

						exit(1);
					}
				}

				strcpy(symbol_table[*symbol_table_size].name, node->childs[1]->name);
				strcpy(symbol_table[*symbol_table_size].type, node->childs[0]->name);
				symbol_table[*symbol_table_size].scope = scope;
				(*symbol_table_size)++;
			}

			for (int p = 0; node->childs[p]; p++)
				make_symbol_table(node->childs[p], symbol_table, symbol_table_size, scope_parents, scope_size, scope, file);
		}
	}
}

parse_tree make_parse_tree(token_stream stream, unsigned size)
{
	for (int i = 0; i < end_point; i++)
	{
		if (i != 0)
			childs[d_by[i]][++childs[d_by[i]][0]] = i;
	}

	parse_node_t* root = malloc(sizeof(parse_node_t));
	for (int i = 0; i < 20; i++)
		root->childs[i] = NULL;
	root->name[0] = '\0';
	root->line = -1;
	root->rule = 0;
	root->symbol = 2001;
	root->scope = 0;

	make_parse_tree_node(root, 0, stream, size);

	return root;
}

void make_parse_tree_node(parse_node_t* node, int num, token_stream stream, unsigned size)
{
	int t = 1;

	for (int r = 0; rules[node->rule].right[r]; r++)
	{
		if (rules[node->rule].right[r] > 2000)
		{
			parse_node_t* nn = malloc(sizeof(parse_node_t));

			for (int i = 0; i < 20; i++)
				nn->childs[i] = NULL;
			nn->name[0] = '\0';
			nn->line = -1;
			nn->rule = d_by_rule[childs[num][t]];
			nn->symbol = rules[d_by_rule[childs[num][t]]].left;
			nn->scope = 0;

			node->childs[r] = nn;
			make_parse_tree_node(nn, childs[num][t], stream, size);
			t++;
		}
		else
		{
			parse_node_t* nn = malloc(sizeof(parse_node_t));

			for (int i = 0; i < 20; i++)
				nn->childs[i] = NULL;
			strcpy(nn->name, stream[idx].name);
			nn->line = stream[idx].line;
			nn->rule = -1;
			nn->symbol = stream[idx].token;
			nn->scope = 0;
			idx++;

			node->childs[r] = nn;
		}
	}
}