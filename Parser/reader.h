#ifndef READER_H
#define READER_H

#include "datastc.h"
#include <stdio.h>
#include <stdbool.h>

scanned_stream read_file(FILE* fp, unsigned* size, unsigned* cap, char file[1024][1024]);
bool split_by1(const char* buffer, unsigned len);
bool split_by2(const char* buffer, unsigned len);

#endif