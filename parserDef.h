/*
BATCH 10
MOHIT MINHAS - 2010A7PS084P
VISHNU DUTT PALADUGU - 2010A7PS029P
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef FILE * grammar;

#define treeStart 200
typedef enum {program,mainFunction,otherFunctions,function,input_par,output_par,parameter_list,dataType,primitiveDatatype,constructedDatatype,remaining_list,stmts,typeDefinitions,typeDefinition,fieldDefinitions,fieldDefinition,moreFields,declarations,declaration,global_or_not,otherStmts,stmt,assignmentStmt,singleOrRecId,A,funCallStmt,outputParameters,inputParameters,iterativeStmt,conditionalStmt,elsePart,ioStmt,allVar,arithmeticExpression,expPrime,term,termPrime,factor,highPrecedenceOperator,lowPrecedenceOperators,all,temp,booleanExpression,var,logicalOp,relationalOp,returnStmt,optionalReturn,idList,more_ids,TOTNT,TK_ASSIGNOP,TK_COMMENT,TK_FIELDID,TK_ID,TK_NUM,TK_RNUM,TK_FUNID,TK_RECORDID,TK_WITH,TK_PARAMETERS,TK_END,TK_WHILE,TK_TYPE,TK_MAIN,TK_GLOBAL,TK_PARAMETER,TK_LIST,TK_SQL,TK_SQR,TK_INPUT,TK_OUTPUT,TK_INT,TK_REAL,TK_SEM,TK_COLON,TK_DOT,TK_ENDWHILE,TK_OP,TK_CL,TK_IF,TK_THEN,TK_ENDIF,TK_READ,TK_WRITE,TK_RETURN,TK_PLUS,TK_MINUS,TK_MUL,TK_DIV,TK_CALL,TK_RECORD,TK_ENDRECORD,TK_ELSE,TK_AND,TK_OR,TK_NOT,TK_LT,TK_EQ,TK_GT,TK_GE,TK_LE,TK_NE,TK_COMMA,$,eps,TOTT,NOTERM} terms;

typedef int table[TOTNT][TOTT];

typedef enum {FALSE,TRUE} Boolean;

struct _stacknode;

typedef struct _stacknode *StackNode;

typedef struct _stacknode
{
    terms dat;
    StackNode next;
};

typedef struct
{
    StackNode top;
    unsigned int size;
    Boolean error;
} Stack;


typedef struct
{
    terms val;
    int ln;
    int ruleno;
    char lexeme[20];
    struct pTree* child[20];
    struct pTree* parent;
} pTree;

typedef pTree *parseTree;

typedef parseTree AST;

