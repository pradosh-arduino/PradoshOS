#pragma once
#include <stdint.h>
#include <stddef.h>

int strlen(char s[]);
void append(char s[], char n);
int __strcmp(char s1[], char s2[]);
void* __memmove(void *dest, const void *src, size_t len);
int __strncmp( const char * s1, const char * s2, size_t n );