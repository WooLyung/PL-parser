#ifndef LEXEME_ARR_H
#define LEXEME_ARR_H

#include "datastc.h"

void lexeme_arr_add(lexeme_t** arr, unsigned* size, unsigned* cap, lexeme_t value);
void lexeme_arr_double(lexeme_t** arr, unsigned* size, unsigned* cap);
lexeme_t make_lexeme(const char* name, unsigned token, unsigned line, bool rwhite);

#endif