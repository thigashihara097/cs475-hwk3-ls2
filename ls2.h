#ifndef LS2_H_INCLUDED
#define LS2_H_INCLUDED

#include "stack.h"

#define TRUE 1
#define FALSE 0
#define INDENT "    "

// Function declarations
char* concatenatePaths(const char* path1, const char* path2);
void printIndentedPath(const char *path, int depth);
void listPathRecursive(const char *path, const char *search, int depth);
void listPath(const char *path, const char *search, int isRecursive);

#endif
