/*
BATCH 10
MOHIT MINHAS - 2010A7PS084P
VISHNU DUTT PALADUGU - 2010A7PS029P
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexer.h"
#include"parser.h"
#include"symbolTableDef.h"

static symnode* st;
static symnode* s;
static int infunc=0;
static int indec=0;
static int inrec=0;
static int addx=0;
static char fun[20];
static char typ[20];


void getprimitives(AST PT, FILE *fst)
{

    int i;
    terms val;


    if(PT!=NULL)
    {
        val=PT->val;
        if(val==TK_FUNID || val==TK_MAIN)
        {
            infunc=1;
            strcpy(fun,PT->lexeme);
        }
        if(val==declaration && infunc && !indec)
        {
            indec=1;

            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    getprimitives(PT->child[i],fst);
                }
            }
        }
        else if((val==TK_INPUT || val==TK_OUTPUT) && infunc)
        {
            indec=1;
        }
        else if((val==TK_INT || val==TK_REAL || val==TK_RECORDID) && indec)
        {
            strcpy(typ,PT->lexeme);
        }
        else if(val==TK_ID && indec)
        {
            s->yes=1;
            strcpy(s->lexeme,PT->lexeme);
            strcpy(s->scope,fun);
            strcpy(s->type,typ);
            s->ln=PT->ln;
        }
        else if(val==TK_GLOBAL && indec)
        {
            strcpy(s->scope,"global");
        }
        else if((val==TK_SEM || val==TK_COMMA || val==TK_SQR) && indec)
        {
            if(val!=TK_COMMA)
                indec=0;
            s->next=(symnode*)malloc(sizeof(symnode));
            s=s->next;
            flush(s->scope);
            flush(s->type);
            flush(s->lexeme);
            s->yes=0;
            s->next=NULL;
        }
        else if(val<TOTNT)
        {
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    getprimitives(PT->child[i],fst);
                }
            }
        }
    }
}


void correctrecs(AST PT, FILE *fst)
{
    int i;
    terms val;

    if(PT!=NULL)
    {
        val=PT->val;
        if(val==typeDefinition)
        {
            inrec=1;
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    correctrecs(PT->child[i],fst);
                }
            }
        }
        else if(val==TK_RECORDID && inrec)
        {
            flush(fun);
            strcpy(fun,PT->lexeme);
            flush(typ);
        }
        else if((val==TK_INT || val==TK_REAL) && inrec && !addx)
        {
            strcat(typ,PT->lexeme);
            addx=1;
        }
        else if((val==TK_INT || val==TK_REAL) && inrec && addx)
        {
            strcat(typ," x ");
            strcat(typ,PT->lexeme);
        }
        else if(val==TK_ENDRECORD && inrec)
        {
            inrec=0;
            addx=0;
            s=st;
            while(s->yes)
            {
                if(s->yes)
                {
                    if(!strcmp(fun,s->type))
                    {
                        strcpy(s->type,typ);
                    }
                    s=s->next;
                }
            }
        }


        else if(val<TOTNT)
        {
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    correctrecs(PT->child[i],fst);
                }
            }
        }
    }
}



void createSymTab(AST PT)
{
    FILE *fst=fopen("stabout.txt","w");
    st=(symnode*)malloc(sizeof(symnode));
    s=st;
    flush(s->scope);
    flush(s->type);
    flush(s->lexeme);
    s->yes=0;
    s->next=NULL;
    int i;
    strcpy(fun,"none");
    getprimitives(PT,fst);
    correctrecs(PT,fst);
    s=st;
    printf("\n");
    while(s->yes)
    {
        if(s->yes)
        {
            fprintf(fst,"%s %s %s\n",s->lexeme,s->type,s->scope);
            printf("%s %s %s\n",s->lexeme,s->type,s->scope);
            s=s->next;
        }
    }
    symnode* s2;
    s2=st;
    return s2;
}
