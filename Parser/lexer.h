#ifndef LEXER_H
#define LEXER_H

#include "datastc.h"

token_stream lexical_analysis(scanned_stream stream, unsigned* size, unsigned* cap);
bool complete_lexer(token_stream stream, unsigned size, char file[1024][1024]);

unsigned check_keyword(const char* name);
unsigned check_sign(const char* name);
unsigned check_identifier(const char* name); // [a-zA-Z_]+[a-zA-Z0-9_]*

bool check_int(const char* name); // [0-9]+
bool check_int_e(const char* name); // [0-9]+[eE]
bool check_e_int(const char* name); // [eE][0-9]+
bool check_int_e_int(const char* name); // [0-9]+[eE][0-9]+
unsigned get_num_part(const char* name);
unsigned check_integer(scanned_stream stream, unsigned size, unsigned i);
unsigned check_double(scanned_stream stream, unsigned size, unsigned i);

#endif