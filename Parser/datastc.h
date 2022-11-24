#ifndef DATASTC_H
#define DATASTC_H

#define MAX_LEXEME_LEN 64

#include <stdbool.h>

typedef struct lexeme
{
	char name[MAX_LEXEME_LEN];
	int token;
	int line;
	bool rwhite;
} lexeme_t;

typedef struct parse_node
{
	int rule; // -1:terminal
	char name[MAX_LEXEME_LEN]; // :null:nonterminal
	int symbol;
	int line;
	struct parse_node* childs[20];
} parse_node_t;

typedef struct symbol_entry
{
	char type[MAX_LEXEME_LEN];
	char name[MAX_LEXEME_LEN];
	int scope;
} symbol_entry_t;

typedef struct terminal
{
	int token;
	int d_by;
} terminal_t;

typedef lexeme_t* scanned_stream;
typedef lexeme_t* token_stream;	
typedef parse_node_t* parse_tree;
typedef terminal_t* terminals;

#endif

/*
 * token number		token name
 * 0					none
 * 1					identifier
 * 2					int constant
 * 3					double constant
 * 4					+
 * 5					-
 * 6					*
 * 7					/
 * 8					%
 * 9					<
 * 10					<=
 * 11					>
 * 12					>=
 * 13					=
 * 14					==
 * 15					!=
 * 16					&&
 * 17					||
 * 18					!
 * 19					;
 * 20					,
 * 21					.
 * 22					[
 * 23					]
 * 24					(
 * 25					)
 * 26					{
 * 27					}
 * 28					[]
 * 29					int
 * 30					double
 * 31					bool
 * 32					string
 * 33					void
 * 34					break
 * 35					class
 * 36					else
 * 37					extends
 * 38					for
 * 39					if
 * 40					new
 * 41					null
 * 42					return
 * 43					this
 * 44					while
 * 45					static
 * 46					Print
 * 47					instanceof
 * 48					NewArray
 * 49					implements
 * 50					interface
 * 51					switch
 * 52					case
 * 53					default
 * 54					string constant
 * 55					bool constant
 * 56					:
 * 
 * 1001					pure integer [0-9]+
 * 1002					pure integer + E [0-9]+[eE]
 * 1003					E + pure integer [eE][0-9]+
 * 1004					pure integer + E + pure integer [0-9]+[eE][0-9]+
 * 1005					dot .
 * 1006					sign [+-]
 * 1007					E [eE]
 * 
 * 2001					Program
 * 2002					Decls
 * 2003					Decl
 * 2004					VariableDecl
 * 2005					Variable
 * 2006					Type
 * 2007					FunctionDecl
 * 2008					Formals
 * 2009					Variables
 * 2010					ClassDecl
 * 2011					Extends
 * 2012					Implements
 * 2013					Implements1
 * 2014					Fields
 * 2015					Field
 * 2016					InterfaceDecl
 * 2017					Prototypes
 * 2018					Prototype
 * 2019					StmtBlock
 * 2020					VariableDecls
 * 2021					Stmts
 * 2022					Stmt
 * 2023					IfStmt
 * 2024					WhileStmt
 * 2025					ForStmt
 * 2026					ReturnStmt
 * 2027					BreakStmt
 * 2028					PrintStmt
 * 2029					Exprs
 * 2030					SwitchStmt
 * 2031					CaseStmts
 * 2032					CaseStmt
 * 2033					DefaultStmt
 * 2034					Expr
 * 2035					LValue
 * 2036					Call
 * 2037					Actuals
 * 2038					Constant
 * 2039					ExprT
 */