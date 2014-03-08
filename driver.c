/*
BATCH 10
MOHIT MINHAS - 2010A7PS084P
VISHNU DUTT PALADUGU - 2010A7PS029P
*/

// SOMETIMES, FOR testcase1 (ORIGINAL) ONLY, THE PROGRAM GIVES ERROR IF TOKENS ARE PRINTED ON SCREEN FIRST AND THEN PARSER IS CALLED.
// BOTH MODULES WORK FINE INDEPENDENTLY, EVEN FOR testcase1.
// SIMCE THEY WORK PROPERLY EVEN TOGETHER FOR ALL OTHER CASES, THE ABOVE ERROR IS PROBABLY SOME COMPILER RELATED ISSUE.

// testcase3_stage2 GIVES ERROR WHILE PARSING. THIS IS BECAUSE OF SOME INCORRECT GRAMMAR RULE.

// FUNCTION CREATEABSTRACTSYNTAXTREE IMPLEMENTED INCORRECTLY, GIVEN IN COMMENTS OF PARSER.C

// PLEASE REMOVE SEMICOLON FROM AFTER ENDWHILE IN CASE OF ERROR. IT WAS NOT SPECIFIED IN THE GRAMMAR AND THUS IS ERRONEOUS.

// FUNCTION IDENTIFIER LENGTH CAN BE MAX 20 INCLUSIVE OF PRECEDING _ SYMBOL. THUS, PLEASE SHORTEN APPROPRIATELY.
// FOR EG, _computeFunctionValue WOULD GIVE ERROR AS IT IS 21 CHARACTERS.



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexer.h"
#include"parser.h"
#include"symbolTable.h"
#include"semanticAnalyzer.h"

int main()
{
    int choice;
    grammar G;
    G=fopen("grammar.txt","r");
    table T;
    parseTree P;
    Symtab S;
    char* cp;
    printf("LEVEL 3: Symbol table/type Checker/Semantic Analyzer modules work\n");
    printf("Enter the input file name with extension\n");
    cp=(char*)malloc(20*sizeof(char));
    flush(cp);
    scanf("%s",cp);
    printf("Enter the choice of operation\n");
    scanf("%d",&choice);

    switch(choice)
    {


    case 1:
        printTokenlist(cp);
        break;
    case 2:
        createParseTable(G,T);
        P=parseInputSourceCode(cp,T,G);
        printParseTree(P);
        break;
    case 3:
        createParseTable(G,T);
        P=parseInputSourceCode(cp,T,G);
        printParseTree(P);
        break;
    case 4:
        createParseTable(G,T);
        P=parseInputSourceCode(cp,T,G);
        S=createSymTab(P);
        break;
    case 5:
        createParseTable(G,T);
        P=parseInputSourceCode(cp,T,G);
        S=createSymTab(P);
        typeCheck(P,S);
        semAnalysis(P,S);
        break;
    case 6:
        printf("Not implemented\n");
        break;

    default:
        printf("Not a valid selection\n");

    }






    return 0;
}

