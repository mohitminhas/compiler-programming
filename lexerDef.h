
/*
BATCH 10
MOHIT MINHAS 2010A7PS084P
VISHNU DUTT PALADUGU  2010A7PS029P
*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE_BUFFER 10
typedef int buffersize;
typedef char buffer[SIZE_BUFFER];
typedef struct
{
    char lexeme[20];
    char *token;
    int lineno;
    struct tokenlist *next;
} tokenlist;
typedef tokenlist *tokenInfo;
typedef struct
{
    FILE *fp;
    int v;
} ret;
