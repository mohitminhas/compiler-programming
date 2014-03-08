/*
BATCH 10
MOHIT MINHAS - 2010A7PS084P
VISHNU DUTT PALADUGU - 2010A7PS029P
*/

#include"parserDef.h"
extern void createParseTable(grammar G, table T);
extern parseTree parseInputSourceCode(char *testcaseFile, table T,grammar G);
extern void printParseTree(parseTree PT);
extern terms charptoenum(char* cp);
extern char* enumtocharp(terms t);
extern char* StringSeparator(char** string, const char* delim); //FUNCTION IMPLEMENTED SINCE STRTOK IS NOT THREAD SAFE
extern void dfs_tree(pTree *PT);
