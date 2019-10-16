#ifndef POEMSORT_H
#define POEMSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

void file_params(FILE* file, int* nCount, long int* charCount);
char* file_to_array(FILE* file, long int charCount);
struct String * text2lines(char text[], int nCount);
int sort1(const void *a, const void *b);
int sort2(const void *a, const void *b);
char* noPunct(char *inp);
int strcmpX (const char *p1, const char *p2);
int strcmpRev (const char *p1, const char *p2);

#endif
