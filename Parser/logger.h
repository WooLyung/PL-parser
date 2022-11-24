#ifndef LOGGER_H
#define LOGGER_H

#define LOG_I(str, ...) printf("[INFO] "); printf(str, __VA_ARGS__); printf("\n");
#define LOG_E(str, ...) fprintf(stderr, "[ERROR] "); printf(str, __VA_ARGS__); printf("\n");

#endif