
/*
BATCH 10
MOHIT MINHAS 2010A7PS084P
VISHNU DUTT PALADUGU  2010A7PS029P
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char scope[20];
    char lexeme[20];
    char type[20];
    int ln;
    int yes;
    struct symnode* next;
} symnode;

typedef symnode *Symtab;
