
/*
BATCH 10
MOHIT MINHAS 2010A7PS084P
VISHNU DUTT PALADUGU  2010A7PS029P
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexer.h"
#include"parser.h"
#include"semanticAnalyzerDef.h"
#include"symbolTable.h"

static symnode* s;
static char fun[20];
static int funcall=0;
static int fundef=0;
static int inwhile=0;
static int whilecond=0;
static int whilevarfound=0;
static int whileSt=0;
static int whileEnd=0;
static int fundeffound=0;
static int assignLHS=0;
static int assignRHS=0;
static int inopar=0;
static int lnoferropar=0;
static int inoptret=0;
static strlist* flist;
static strlist* fl;

void clearall()
{
    flush(fun);
    fundef=0;
    funcall=0;
    inwhile=0;
    whilecond=0;
    whilevarfound=0;
    whileSt=0;
    whileEnd=0;
    fundeffound=0;
    assignLHS=0;
    assignRHS=0;
    lnoferropar=0;
    inoptret=0;
    inopar=0;

}


void undeclaredVar(AST PT, Symtab st)
{
    int i;
    terms val;
    if(PT!=NULL)
    {
        val=PT->val;
        if(val==funCallStmt)
        {
            funcall=1;
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    undeclaredVar(PT->child[i],st);
                }
            }
        }
        else if((val==TK_FUNID || val==TK_MAIN) && !funcall)
        {
            strcpy(fun,PT->lexeme);
        }
        else if(val==TK_ID)
        {
            int found=0;
            s=st;

            while(s->yes)
            {
                if(s->yes)
                {
                    if((!strcmp(PT->lexeme,s->lexeme) && !strcmp(fun,s->scope)) || (!strcmp(PT->lexeme,s->lexeme) && !strcmp(s->scope,"global")))
                    {
                        found=1;
                        break;
                    }
                    s=s->next;
                }
            }
            if(!found)
            {
                printf("line %d: variable %s not declared\n",PT->ln,PT->lexeme);
            }
        }
        else if(val==TK_SEM && funcall)
        {
            funcall=0;
        }
        else if(val<TOTNT)
        {
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    undeclaredVar(PT->child[i],st);
                }
            }
        }
    }
}

void multipleDecnGlobal(Symtab st)
{
    symnode* sd;
    sd=st;
    while(sd->yes)
    {
        if(!sd->yes)
            break;
        if(sd->next!=NULL)
            s=sd->next;
        while(s->yes)
        {
            if(!sd->yes)
                break;
            if(!strcmp(sd->lexeme,s->lexeme))
            {

                if(sd->yes)
                {
                    if(!strcmp(sd->scope,s->scope) && strcmp(sd->scope,"global"))
                        printf("line %d: The identifier <%s> is declared more than once\n",sd->ln,sd->lexeme);
                    else if(!strcmp(sd->scope,"global"))
                        printf("line %d: Variable <%s> being a global variable cannot be declared more than once\n",s->ln,s->lexeme);
                    else if(!strcmp(s->scope,"global"))
                        printf("line %d: Variable <%s> being a global variable cannot be declared more than once\n",sd->ln,sd->lexeme);
                }
            }
            if(s->next!=NULL)
                s=s->next;
        }
        if(sd->next!=NULL)
            sd=sd->next;
    }
}


/*void checkCall(AST PT)
{
    int i;
    terms val;
    if(PT!=NULL)
    {
        val=PT->val;
        if(val==function)
        {
            fundef=1;
            checkCall(PT);
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    checkCall(PT->child[i]);
                }
            }
        }
        else if(val<TOTNT)
        {
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    checkCall(PT->child[i]);
                }
            }
        }
    }
}




void parameterCheck(AST PT)
{
    int i;
    terms val;
    if(PT!=NULL)
    {
        val=PT->val;
        if(val==function)
        {
            fundef=1;
            checkCall(PT);
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    parameterCheck(PT->child[i]);
                }
            }
        }

        else if(val<TOTNT)
        {
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    parameterCheck(PT->child[i]);
                }
            }
        }
    }
}

void ifBool(AST PT)
{
    int i;
    terms val;
    if(PT!=NULL)
    {
        val=PT->val;
        if(val==TK_IF)
        {
            ifst=1;
        }
//        else if(val==)
        else if(val==TK_THEN && ifst)
        {
            ifst=0;
        }
        else if(val<TOTNT)
        {
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    parameterCheck(PT->child[i]);
                }
            }
        }
    }
}*/

void recursiveCallnFunCallOrder(AST PT)
{
    int i;
    terms val;
    if(PT!=NULL)
    {
        val=PT->val;
        if(val==funCallStmt)
        {
            funcall=1;
            for(i=0; i<20; i++)
            {
                if(PT->child[i]!=NULL)
                {
                    recursiveCallnFunCallOrder(PT->child[i]);
                }
            }
        }
        else if(val==TK_FUNID && funcall)
        {
            strlist* fd;
            fd=flist;
            while(fd->ln)
            {
                if(fd->ln)
                {
                    if(!strcmp(fd->fun,PT->lexeme))
                    {
                        fundeffound=1;
                        break;
                    }
                    if(fd->next)
                        fd=fd->next;
                }
            }
            if(!fundeffound)
            {
                printf("line %d: The function %s is undefined\n",PT->ln,PT->lexeme);
            }


        }
        else if(val==TK_FUNID && !fundef)
        {
            fundef=1;
            strcpy(fun,PT->lexeme);
            if(!funcall && fun!=TK_MAIN)
            {
                strcpy(fl->fun,PT->lexeme);
                fl->ln=PT->ln;
                fl->next=(strlist*)malloc(sizeof(strlist));
                fl=fl->next;
                fl->ln=0;
                fl->next=NULL;
            }
        }
        else if(val==TK_FUNID && fundef)
        {
            if(!strcmp(fun,PT->lexeme))
            {
                printf("line %d: recursive call to %s\n",PT->ln,PT->lexeme);
            }
        }
        else if(val==TK_END && fundef)
        {
            fundef=0;
        }
        else if(val==TK_SEM && funcall)
        {
            funcall=0;
            fundeffound=0;
        }
        else if(val<TOTNT)
        {
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    recursiveCallnFunCallOrder(PT->child[i]);
                }
            }
        }
    }
}




void ifBool()
{
    return; //ALREADY CHECKED DURING SYNTAX ANALYSIS PHASE
}

void recEverywhere() //RECORD GLOBAL
{
    return; //TAKEN CARE OF WHILE POPULATING SYMBOL TABLE
}


void Overload()
{
    strlist* fd;
    fd=flist;
    while(fd->ln)
    {
        if(fd->next!=NULL)
            fl=fd->next;
        while(fl->ln)
        {
            if(!strcmp(fd->fun,fl->fun))
            {
                printf("line %d: function %s overloaded\n",fl->ln, fl->fun);
            }
            if(fl->next!=NULL)
                fl=fl->next;
        }
        if(fd->next!=NULL)
            fd=fd->next;
    }
}



/*void assignSt(AST PT)
{
    int i;
    terms val;
    if(PT!=NULL)
    {
        val=PT->val;
        if(val==assignmentStmt)
        {
            assignLHS=1;
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    assignSt(PT->child[i]);
                }
            }
        }
        else if(val==TK_ID && assignLHS)
        {

        }
        else if(val==TK_ID && assignRHS)
        {

        }
        else if(val==TK_ASSIGNOP && assignLHS)
        {
            assignLHS=0;
            assignRHS=1;
        }
        else if(val==TK_SEM && assignRHS)
        {
            assignRHS=0;
        }
        else if(val<TOTNT)
        {
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    assignSt(PT->child[i]);
                }
            }
        }
    }
}*/


void whileCheck(AST PT)
{
    int i;
    terms val;
    if(PT!=NULL)
    {
        val=PT->val;
        if(val==TK_WHILE)
        {
            whileSt=PT->ln;
            inwhile=1;
        }
        else if(val==booleanExpression && inwhile)
        {
            whilecond=1;
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    whileCheck(PT->child[i]);
                }
            }
        }
        else if(val==TK_ID && whilecond)
        {
            strcpy(fl->fun,PT->lexeme);
            fl->ln=PT->ln;
            fl->next=(strlist*)malloc(sizeof(strlist));
            fl=fl->next;
            fl->ln=0;
            fl->next=NULL;
        }
        if(val==stmt && whilecond)
        {
            whilecond=0;
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    whileCheck(PT->child[i]);
                }
            }
        }
        else if(val==TK_ID && inwhile && !whilecond)
        {
            fl=flist;
            while(fl->ln)
            {
                if(fl->ln)
                {
                    if(!strcmp(fl->fun,PT->lexeme))
                    {
                        whilevarfound=1;
                        break;
                    }
                    if(fl->next)
                        fl=fl->next;
                }
            }
        }
        else if(val==TK_ENDWHILE && inwhile)
        {
            inwhile=0;
            whileEnd=PT->ln;
            if(!whilevarfound)
                printf("line %d-%d: None of the variables participating in the iterations of the while loop get updated\n",whileSt,whileEnd);
        }
        else if(val<TOTNT)
        {
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    whileCheck(PT->child[i]);
                }
            }
        }
    }
}

void ifNoReturn(AST PT)
{
    int i;
    terms val;
    if(PT!=NULL)
    {
        val=PT->val;
        if(val==output_par && !inopar)
        {
            inopar=1;
        }
        else if(val!=eps && inopar)
        {
            lnoferropar=PT->ln;
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    ifNoReturn(PT->child[i]);
                }
            }
        }
        else if(val==TK_SEM && inopar)
        {
            inopar=0;
        }
        else if(val==optionalReturn && !optionalReturn)
        {
            inoptret=1;
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    ifNoReturn(PT->child[i]);
                }
            }
        }
        else if(val==eps && inoptret)
        {
            printf("line %d: function with no return value invoked incorrectly\n",lnoferropar);
        }
        else if(val==TK_SEM && inoptret)
        {
            inoptret=0;
        }
        else if(val<TOTNT)
        {
            for(i=0; i<20; i++)
            {

                if(PT->child[i]!=NULL)
                {
                    ifNoReturn(PT->child[i]);
                }
            }
        }
    }
}





void initflists()
{
    flist=(strlist*)malloc(sizeof(strlist));
    fl=flist;
    fl->ln=0;
    fl->next=NULL;
}


void semAnalysis(AST PT, Symtab st)
{
    printf("\n");
    undeclaredVar(PT,st);
    clearall();
    //parameterCheck(PT);
    clearall();
    initflists();
    recursiveCallnFunCallOrder(PT);
    clearall();
    Overload(); // CALL TO Overload() MUST BE AFTER recursiveCallnFunCallOrder()
    clearall();
    multipleDecnGlobal(st);
    clearall();
    ifBool();
    recEverywhere();
    clearall();
    initflists();
    whileCheck(PT);
    clearall();
    //initflists();
    ifNoReturn(PT);
    clearall();

}
