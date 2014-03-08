/*
BATCH 10
MOHIT MINHAS - 2010A7PS084P
VISHNU DUTT PALADUGU - 2010A7PS029P
*/

// FUNCTION CREATEABSTRACTSYNTAXTREE IMPLEMENTED INCORRECTLY, GIVEN IN COMMENTS
// PLEASE REMOVE SEMICOLON FROM AFTER ENDWHILE IN CASE OF ERROR. IT WAS NOT SPECIFIED IN THE GRAMMAR AND THUS IS ERRONEOUS.
// FUNCTION IDENTIFIER LENGTH CAN BE MAX 20 INCLUSIVE OF PRECEDING _ SYMBOL. THUS, PLEASE SHORTEN APPROPRIATELY.
// FOR EG, _computeFunctionValue WOULD GIVE ERROR AS IT IS 21 CHARACTERS.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexer.h"
#include"parserDef.h"

static int j=-1,flag=0;
static char* c1[TOTNT];
static int id1[100];
static char* d1[TOTNT];
static char* c2[TOTNT];
static int id2[100];
static char* d2[TOTNT];
static char c[100][100];
static int id[100];
static char d[100][100];
static int re=0;
static pTree* p;
static pTree *tempn;
static pTree *par;
static pTree* tpar;
static pTree* tsib;
static int printonscr=1;

terms charptoenum(char* cp)
{
    char* strarr[]= {"program","mainFunction","otherFunctions","function","input_par","output_par","parameter_list","dataType","primitiveDatatype","constructedDatatype","remaining_list","stmts","typeDefinitions","typeDefinition","fieldDefinitions","fieldDefinition","moreFields","declarations","declaration","global_or_not","otherStmts","stmt","assignmentStmt","singleOrRecId","A","funCallStmt","outputParameters","inputParameters","iterativeStmt","conditionalStmt","elsePart","ioStmt","allVar","arithmeticExpression","expPrime","term","termPrime","factor","highPrecedenceOperator","lowPrecedenceOperators","all","temp","booleanExpression","var","logicalOp","relationalOp","returnStmt","optionalReturn","idList","more_ids","TOTNT","TK_ASSIGNOP","TK_COMMENT","TK_FIELDID","TK_ID","TK_NUM","TK_RNUM","TK_FUNID","TK_RECORDID","TK_WITH","TK_PARAMETERS","TK_END","TK_WHILE","TK_TYPE","TK_MAIN","TK_GLOBAL","TK_PARAMETER","TK_LIST","TK_SQL","TK_SQR","TK_INPUT","TK_OUTPUT","TK_INT","TK_REAL","TK_SEM","TK_COLON","TK_DOT","TK_ENDWHILE","TK_OP","TK_CL","TK_IF","TK_THEN","TK_ENDIF","TK_READ","TK_WRITE","TK_RETURN","TK_PLUS","TK_MINUS","TK_MUL","TK_DIV","TK_CALL","TK_RECORD","TK_ENDRECORD","TK_ELSE","TK_AND","TK_OR","TK_NOT","TK_LT","TK_EQ","TK_GT","TK_GE","TK_LE","TK_NE","TK_COMMA","$","eps","TOTT"};
    int i;
    if(cp==NULL)
    {
        return NOTERM;
    }
    for(i=0; i<NOTERM; i++)
    {
        if(strcmp(cp,strarr[i])==0)
        {
            return i;
        }
    }
}

char* enumtocharp(terms t)
{
    char* strarr[]= {"program","mainFunction","otherFunctions","function","input_par","output_par","parameter_list","dataType","primitiveDatatype","constructedDatatype","remaining_list","stmts","typeDefinitions","typeDefinition","fieldDefinitions","fieldDefinition","moreFields","declarations","declaration","global_or_not","otherStmts","stmt","assignmentStmt","singleOrRecId","A","funCallStmt","outputParameters","inputParameters","iterativeStmt","conditionalStmt","elsePart","ioStmt","allVar","arithmeticExpression","expPrime","term","termPrime","factor","highPrecedenceOperator","lowPrecedenceOperators","all","temp","booleanExpression","var","logicalOp","relationalOp","returnStmt","optionalReturn","idList","more_ids","TOTNT","TK_ASSIGNOP","TK_COMMENT","TK_FIELDID","TK_ID","TK_NUM","TK_RNUM","TK_FUNID","TK_RECORDID","TK_WITH","TK_PARAMETERS","TK_END","TK_WHILE","TK_TYPE","TK_MAIN","TK_GLOBAL","TK_PARAMETER","TK_LIST","TK_SQL","TK_SQR","TK_INPUT","TK_OUTPUT","TK_INT","TK_REAL","TK_SEM","TK_COLON","TK_DOT","TK_ENDWHILE","TK_OP","TK_CL","TK_IF","TK_THEN","TK_ENDIF","TK_READ","TK_WRITE","TK_RETURN","TK_PLUS","TK_MINUS","TK_MUL","TK_DIV","TK_CALL","TK_RECORD","TK_ENDRECORD","TK_ELSE","TK_AND","TK_OR","TK_NOT","TK_LT","TK_EQ","TK_GT","TK_GE","TK_LE","TK_NE","TK_COMMA","$","eps","TOTT"};
    int i;
    if(t==NOTERM)
        return NULL;
    for(i=0; i<NOTERM; i++)
    {
        if(t==i)
            return strarr[i];
    }
}

char* StringSeparator(char** string, const char* delim) //FUNCTION IMPLEMENTED SINCE STRTOK IS NOT THREAD SAFE
{
    char* start = *string;
    char* a;

    a = (start != NULL) ? strpbrk(start, delim) : NULL;

    if (a == NULL)
    {
        *string = NULL;
    }
    else
    {
        *a = '\0';
        *string = a + 1;
    }

    return start;
}



/*int countChars( char* s, char ch )
{
    return *s == '\0'
           ? 0
           : countChars( s + 1, ch ) + (*s == ch);
}*/





terms getfirst(terms t,FILE *fp,FILE *fout)
{
    char *skip;
    skip=(char*)malloc(200*sizeof(skip));
    terms ter;
    char ch;
    terms temp;
    char *p;
    p=(char *)malloc(30*sizeof(char));


    char *q;
    q=(char*)malloc(20*sizeof(char));
    while (!feof(fp))
    {
        fscanf(fp,"%s",q);

        ter=charptoenum(q);
        if(ter==t)
        {
            ch=getc(fp);
            d1[ter]=(char*)malloc(200*sizeof(char));
            fgets(d1[ter],200,fp);
            d1[ter]=StringSeparator(&d1[ter],"\n");
            break;

        }
        else
        {

            fgets(skip,200,fp);
        }
        if((ch=getc(fp))=='$')
            break;
        else
            fseek(fp,-1,SEEK_CUR);
    }
    rewind(fp);
    p=StringSeparator(&d1[ter]," ");
    int r=0;
    for(r=0; r<id1[ter]; r++)
    {
        p=StringSeparator(&d1[ter]," ");
    }
    id1[ter]++;
    temp=charptoenum(p);
    return temp;
}

terms getfollow(terms t,FILE *fp,FILE *fout)
{

    char* skip;
    skip=(char*)malloc(200*sizeof(char));
    terms ter;
    char ch;
    terms temp;
    char *p;
    p=(char *)malloc(30*sizeof(char));
    char *q;
    q=(char*)malloc(20*sizeof(char));

    while (!feof(fp))
    {
        fscanf(fp,"%s",q);

        ter=charptoenum(q);
        if(ter==t)
        {

            ch=getc(fp);
            d2[ter]=(char*)malloc(200*sizeof(char));
            fgets(d2[ter],200,fp);
            d2[ter]=StringSeparator(&d2[ter],"\n");

            break;


        }
        else
        {
            fgets(skip,200,fp);
            skip=StringSeparator(&skip,"\n");
        }

        if((ch=getc(fp))=='$')
            break;
        else
            fseek(fp,-1,SEEK_CUR);
    }
    rewind(fp);
    p=StringSeparator(&d2[ter]," ");
    int r;
    for(r=0; r<id2[ter]; r++)
    {
        p=StringSeparator(&d2[ter]," ");
    }
    id2[ter]++;



    temp=charptoenum(p);

    return temp;
}


int getrule(terms lhs, terms ter, FILE* ffirst, grammar G,FILE *fout)
{
    int h=-1; //THIS HAS TO BE DONE BECAUSE STRTOK MODIFIES THE ORIGINAL STRING
    rewind(G);
    while(!feof(G))
    {
        h++;
        fscanf(G,"%d %s %s",&id[h],c[h],d[h]);

    }
    int i,f1,f2,x,w,r;
    terms n;
    char *p;
    p=(char*)malloc(30*sizeof(char));
    terms temp;
    for(i=0; i<=j; i++)
    {

        if(lhs==charptoenum(c[i]))
        {
            p=strtok(d[i],"~");
            n=charptoenum(p);
LABEL1:
            if(n==ter)
            {
                id1[n]=0;
                return id[i];
            }

            else if(n<TOTNT)
            {
                f1=0;
                f2=0;

                temp=getfirst(n,ffirst,fout);

                while(temp!=NOTERM)
                {
                    if(temp==eps)
                    {
                        f2=1;
                        break;

                    }
                    else if(temp==ter)
                    {
                        f1=1;
                        id1[n]=0;
                        return id[i];
                    }
                    temp=getfirst(n,ffirst,fout);
                }
                id1[n]=0;
                if(f1==0 && f2==0)
                    continue;
                if(f1==0 && f2==1)
                {
                    if(flag==0)
                    {
                        r=i;
                        flag=1;
                    }
                    p=strtok(NULL,"~");
                    n=charptoenum(p);
                    if(n!=NOTERM)
                    {
                        id1[n]=0;
                        goto LABEL1;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else continue;
        }
    }
    return -1;
}

void createParseTable(grammar G, table T)
{
    FILE * ffirst=fopen("first.txt","r");
    FILE * ffollow=fopen("follow.txt","r");
    FILE * fout=fopen("output.txt","w");
    terms temp;
    int k,l,x,y;
    for(k=0; k<TOTNT; k++)
        for(l=0; l<(TOTT); l++)
            T[k][l]=-1;
    while(!feof(G))
    {
        j++;
        fscanf(G,"%d %s %s",&id[j],c[j],d[j]);

    }

    terms n,temp2;
    for(k=0; k<=j; k++)
    {
        n=charptoenum(c[k]);
        temp=getfirst(n,ffirst,fout);
        while(temp!=NOTERM)
        {
            if(temp!=eps)
            {
                if(T[n][temp]==-1)
                {
                    T[n][temp]=getrule(n,temp,ffirst,G,fout);
                }
                temp=getfirst(n,ffirst,fout);
            }
            if(temp==eps)
            {
                temp2=getfollow(n,ffollow,fout);
                while(temp2!=NOTERM)
                {
                    if(T[n][temp2]==-1)
                    {
                        T[n][temp2]=id[k]+1;
                    }
                    temp2=getfollow(n,ffollow,fout);
                }
                temp=getfirst(n,ffirst,fout);
            }
            id2[n]=0;
        }
        id1[n]=0;
    }
    int h=-1; //THIS HAS TO BE DONE BECAUSE STRTOK MODIFIES THE ORIGINAL STRING
    rewind(G);
    while(!feof(G))
    {
        h++;
        fscanf(G,"%d %s %s",&id[h],c[h],d[h]);

    }

    fclose(ffirst);
    fclose(ffollow);
}


Stack createStack()
{
    Stack s;
    s.top = NULL;
    s.size = 0;
    s.error = FALSE;
    return s;
}

Boolean isEmpty(Stack s)
{
    return (s.top==NULL) ? TRUE : FALSE;
}

terms top(Stack s)
{
    return s.top->dat;
}

Stack push(terms d, Stack s)
{
    Stack s1;

    s1.top = (StackNode)malloc(sizeof(struct _stacknode));
    if (s1.top == NULL)
    {
        s1.error = TRUE; // “out of memory” error
        return s1;
    }

    s1.top->dat = d ; // copy element
    s1.top->next = s.top;
    s1.size = s.size+1;

    return s1;

}

Stack pop(Stack s)
{
    Stack s1;
    StackNode temp;

    temp = s.top ;
    s1.top = s.top->next ; // skip element
    s1.size = s.size-1;

    free(temp);

    return s1;
}



void dfs_tree(pTree *PT, FILE *fptree)
{
    int i;
    terms val;

    if(PT!=NULL)
    {
        val=PT->val;

        if(val>TOTNT && val<$)
        {
            fprintf(fptree,"%s     %d            %s\n",PT->lexeme,PT->ln,enumtocharp(val));
            if(printonscr)
                printf("%s     %d            %s\n",PT->lexeme,PT->ln,enumtocharp(val));

        }
        else if(val<TOTNT || val==eps)
        {
            fprintf(fptree,"--------------           %s\n",enumtocharp(val));
            if(printonscr)
                printf("--------------           %s\n",enumtocharp(val));
            for(i=0; i<20; i++)
            {
                if(PT->child[i]!=NULL)
                {
                    dfs_tree(PT->child[i], fptree);
                }
            }
        }
    }
}

void printParseTree(parseTree PT, char *outfile)
{
    FILE *fptree = fopen(outfile, "w");

    fprintf(fptree,"lexemeCurrentNode     lineno   token\n");
    fprintf(fptree,"\n");
    if(printonscr)
    {
        printf("lexemeCurrentNode     lineno   token\n");
        printf("\n");
    }
    dfs_tree(PT, fptree);
    fclose(fptree);
}


//FUNCTION HAS ERROR


Stack POUR_RHS_OF_RULENO(int k,Stack S, grammar G, FILE *fout,FILE *ftree)
{
    int h=-1; //THIS HAS TO BE DONE BECAUSE STRTOK MODIFIES THE ORIGINAL STRING
    rewind(G);
    while(!feof(G))
    {
        h++;
        fscanf(G,"%d %s %s",&id[h],c[h],d[h]);

    }
    S=pop(S);
    int y,i,x,rule_num;
    for(y=0; y<=j; y++)
    {
        if(id[y]==k)
        {
            rule_num=id[y];
            i=y;
        }
    }
    int A[10];
    int z;
    for(z=0; z<10; z++)
    {
        A[z]=-1;
    }
    terms ter;
    ter=charptoenum(strtok(d[i],"~"));
    z=0;
    A[z]=ter;
    if(tempn!=NULL)
    {
        flushchild();
        par=tempn;
        x=0;
        tempn->child[x]=(pTree*)malloc(sizeof(pTree));
        tempn=tempn->child[x];
        tempn->parent=par;
        flush(tempn->lexeme);
        tempn->ln=-1;
        tempn->ruleno=id[i];
        tempn->val=ter;
        flushchild();
        tempn=par;
    }
    while(ter!=NOTERM)
    {

        ter=charptoenum(strtok(NULL,"~"));
        if(ter!=NOTERM)
        {
            z++;
            A[z]=ter;
            if(tempn!=NULL)
            {
                x++;
                tempn->child[x]=(pTree*)malloc(sizeof(pTree));
                tempn=tempn->child[x];
                tempn->parent=par;
                flush(tempn->lexeme);
                tempn->ln=-1;
                tempn->ruleno=id[i];
                tempn->val=ter;
                flushchild();
                tempn=par;
            }

        }
    }
    tempn=tempn->child[0];
    for(z=9; z>=0; z--)
    {
        if(A[z]!=-1)
        {
            S=push(A[z],S);
        }
    }
    return S;
}


void getsibling(FILE *ftree)
{
    if(tempn!=NULL)
        if(tempn!=p && tempn->val!=program)
        {
            if(tempn==p)
            {
                tsib=NULL;
                return;
            }
            tpar=tempn->parent;
            int w=0;
            while(tpar->child[w]!=NULL)
            {
                if(tpar->child[w]==tempn)
                {
                    break;
                }
                w++;
            }
            int b;
            pTree* tt;
            for(b=0; b<20; b++)
            {
                if(tpar->child[b]!=NULL)
                {
                    tt=tpar->child[b];
                }
            }
            if(tpar->child[w+1]!=NULL)
            {
                tsib=tpar->child[w+1];
            }
            else
            {

                if(tempn==p)
                {
                    tsib=NULL;
                    return;
                }
                tempn=tempn->parent;
                getsibling(ftree);
            }
        }
        else
        {
            tsib=NULL;
        }
    if(tsib==NULL)
        fprintf(ftree,"tsib=NULL\n");
    fprintf(ftree,"EXIT getsib\n");
    return;
}

void flushchild()
{
    int b;
    for(b=0; b<20; b++)
    {
        tempn->child[b]=NULL;
    }
    return;
}

//FUNCTION HAS ERROR


parseTree parseInputSourceCode(char *testcaseFile, table T,grammar G)
{
    FILE *fin=fopen(testcaseFile,"r");
    Stack S=createStack();
    terms lookahead;
    tokenInfo info=NULL;
    info=getNextToken(fin,SIZE_BUFFER,info);
    lookahead=charptoenum(info->token);
    pTree* p;
    p=(pTree*)malloc(sizeof(pTree));
    tempn=p;
    S=push($,S);
    S=push(program,S);
    flush(tempn->lexeme);
    tempn->ln=-1;
    tempn->ruleno=-1;
    tempn->val=program;
    tempn->parent=NULL;
    flushchild();
    par=tempn;
    int x;
    while(1)
    {
        if(lookahead==TK_COMMENT)
        {
            info=getNextToken(fin,SIZE_BUFFER,info);
            lookahead=charptoenum(info->token);
            continue;
        }
        if(top(S)==eps)
        {
            S=pop(S);
            if(tempn!=NULL)
            {
                if(tempn!=p)
                {
                    if(tempn->val==eps)
                    {
                        getsibling(ftree);
                        if(tsib==NULL)
                            continue;
                        tempn=tsib;
                        flushchild();
                        tpar=tempn->parent;
                    }
                }
            }

            continue;
        }
        if(top(S)==$ && lookahead==NOTERM)
        {
            printf("Compiled Successfully: Input source code is syntactically correct!!\n");
            break;
        }
        else if(top(S)==$ && lookahead!=NOTERM)
        {
            printf("ERROR: Incomplete code\n");
            break;
        }
        else if(top(S)!=$ && lookahead==NOTERM)
        {
            printf("ERROR: Wrong syntax\n");
            break;
        }
        if(top(S)>TOTNT && top(S)<$)
        {
            if(lookahead==top(S))
            {
                if(tempn!=NULL && tempn!=p)
                {
                    if(lookahead==tempn->val)
                    {
                        tempn->ln=info->lineno;
                        strcpy(tempn->lexeme,info->lexeme);
                    }
                }
                info=getNextToken(fin,SIZE_BUFFER,info);
                lookahead=charptoenum(info->token);
                S=pop(S);
                getsibling(ftree);
                if(tsib==NULL)
                    continue;
                if(tempn!=p)
                {
                    tempn=tsib;
                    tpar=tempn->parent;
                }
            }
            else if(lookahead!=top(S))
            {
                break;
            }
        }
        else if(top(S)<TOTNT)
        {
            terms X = top(S);
            if(T[X][lookahead]!=-1)
                S=POUR_RHS_OF_RULENO(T[X][lookahead],S,G,fout,ftree);
            else
            {
                printf("Error 5: Incorrect token or token missing. Exiting");
                break;
            }
        }
    }
    return p;
}


/*
#include<stdio.h>
#include<stdlib.h>
#include"parserDef.h"

void createAbstractSyntaxtree(parseTree P ,abstractSyntaxTree A)   // P, A are pointers to the root node
{
    copyTree(P,A);
     abstractSyntaxTree temp;
     temp=A;
     while(temp!=NULL)
     {
     action(temp);




     }

}

void action(abstractSyntaxTree temp)
{
    switch(temp->val)

    case program: pull(temp,mainFunction); break;
    case mainFunction: pull(temp,stmts); break;
        case otherFunctions:
    if(temp->child[0]->val==eps)
     del(otherFunctions);
     else
     pull(temp,function); break;
    case function: pull(temp,TK_FUNID); break;
    case input_par: pull(temp,parameter_list); break;
    case output_par:
    if(temp->child[0]->val==eps);
    else pull(temp,parameter_list); break;
    case parameter_list: pull (TK_ID); break;
    case datatype: pull(temp,temp->child[0]->val); break;
    case primitiveDatatype: pull(temp,temp->child[0]->val); break;
    case constructedDatatype: pull(temp,TK_RECORDID); break;
    case remaining_list: pull(temp,TK_COMMA); break;
    case stmts: pull(temp,returnStmt); break;
    case typeDefinitions:
    if(temp->child[0]->val==eps)
     del(typeDefinitions);
     else
     pull(temp,typeDefinition); break;
     case typeDefinition: pull(temp,TK_RECORDID); break;
     case fieldDefinitions: pull(temp,fieldDefinition); break;
     case fieldDefinition: pull(temp,TK_FIELDID); break;
     case moreFields:
     if(temp->child[0]->val==eps)
     del(moreFields);
     else
     pull(temp,fieldDefinition); break;
     case declarations:
     if(temp->child[0]->val==eps)
     del(declarations);
     else
     pull(temp,declaration); break;
     case declaration: pull(temp,TK_ID); break;
     case global_or_not:
     if(temp->child[0]->val==eps)
     del(global_or_not);
     else
     pull(temp,TK_GLOBAL); break;
     case otherStmts:
     if(temp->child[0]->val==eps)
     del(otherStmts);
     else
     pull(temp,stmt); break;
     case stmt:  pull(temp,temp->child[0]->val); break;
     case assignmentStmt: pull(temp,TK_ASSIGNOP); break;
     case sindleOrRecId: pull(temp,TK_ID); break;
     case A:
     if(temp->child[0]->val==eps)
     del(A);
     else
     pull(temp,TK_DOT); break;
     case funCallStmt: pull(temp,TK_FUNID); break;
     case outputParameters:
     if(temp->child[0]->val==eps)
     del(outputParameters);
     else
     pull(temp,TK_ASSIGNOP); break;
     case inputParameters: pull(temp,idList); break;
     case iterativeStmt: pull(temp,TK_WHILE); break;
     case conditionalStmt: pull(temp,TK_IF); break;
     case elsePart: pull(temp,term->child[0]->val); break;
     case ioStmt: pull(temp,term->child[0]->val); break;
     case allVar: pull(temp,term->child[0]->val); break;
     case aithmeticExpression: pull(temp,term); break;
     case expPrime:
     if(temp->child[0]->val==eps)
     del(expPrime);
     else
     pull(temp,term); break;
     case term: pull(temp,factor); break;
     case termPrime:
     if(temp->child[0]->val==eps)
     del(termPrime);
     else
     pull(temp,factor): break;
     case factor:
     if(term->child[0]->val==TK_OP)
     pull(temp,arithmeticExpression);
     else
     pull(temp,all); break;
     case highPrecedenceOperator:
     pull(temp,term->child[0]->val); break;
     case lowPrecedenceOperator:
     pull(temp,term->child[0]->val); break;
     case all: pull(temp,term->child[0]->val); break;
     case temp:
     if(term->child[0]->val==eps)
     del(temp);
     else
     pull(temp,TK_FIELDID); break;
     case booleanExpression:
     if(term->child[0]->val==TK_OP)
     pull(temp,logicalOp);
     else if(term->child[0]->val==var)
     pull(temp,relationalOp);
     else pull(temp,TK_NOT); break;
     case var: pull(temp,term->child[0]->val); break;
     case logicalOp:  pull(temp,term->child[0]->val); break;
     case relationalOp:  pull(temp,term->child[0]->val); break;
     case returnStmt: pull(temp,optionalReturn); break;
     case optionalReturn:
     if(term->child[0]->val==eps)
     del(optionalReturn);
     else
     pull(temp,idList); break;
     case idLIst: pull(temp,TK_ID); break;
     case more_ids:
     if(term->child[0]->val==eps)
     del(more_ids);
     else
     pull(temp,TK_COMMA); break;

     case TK_SQL:
     case TK_SQR:
     case TK_INPUT:
     case TK_LIST:
     case TK_PARAMETER:
     case TK_SEM:
     case TK_TYPE:
     case TK_WITH:
     case TK_PARAMETERS:
     case TK_THEN:
     del(temp); break;

     default: nop(term);
     break;
}

  void copyTree(parseTree P,abstractSyntaxTree A)
{
    int i=0;
   A=(abstractSyntaxTree)malloc(sizeof(ASTree));
   A->val=P->val;
   A->child=NULL;
   while(P->child[i]!=NULL)
   {
       copyTree(P->child[i],A->child[i]);
       i++;
   }
}
 void pull(abstractSyntaxTree temp,terms v)
{
     int i=0;
     while(temp->child[i]!=NULL)
     {
         if(temp->child[i]->val==v)
   {temp=temp->child[i];
         break;}
         else i++;

     }
}
  void nop(abstractSyntaxTree temp)
{
    return;
}
 void del(abstractSyntaxTree temp)
 {

     free(temp);
 }

 }
*/









