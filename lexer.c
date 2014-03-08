
/*
BATCH 10
MOHIT MINHAS 2010A7PS084P
VISHNU DUTT PALADUGU  2010A7PS029P
*/


// FUNCTION IDENTIFIER LENGTH CAN BE MAX 20 INCLUSIVE OF PRECEDING _ SYMBOL. THUS, PLEASE SHORTEN APPROPRIATELY.
// FOR EG, _computeFunctionValue WOULD GIVE ERROR AS IT IS 21 CHARACTERS.


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"lexerDef.h"

ret getStream(FILE *fp, buffer B, buffersize k)
{
    ret r;
    int i;
    r.v=fread(B,sizeof(char),k,fp);
    r.fp=fp;
    if(feof(fp))
        if(r.v<10)
        {
            for(i=r.v; i<SIZE_BUFFER; i++)
                B[i]='$';
        }
    return r;
}
void flush(char id[])
{
    int n;
    for(n=0; n<20; n++)
    {
        id[n]='\0';
    }
}
/*void copy(char a[], char b[])
{
        int i=0;
        for(i=0;i<20;i++)
            a[i]=b[i];
}*/


tokenInfo getNextToken(FILE *fp, buffersize k, tokenInfo t)
{

    if(t==NULL)
    {
        tokenInfo ts,tl;
        int i,j,s=0,ln=1,l=0,temp=0,x=0;
        char c,d,e, id[20];
        ret r;
        flush(id);
        ts=(tokenInfo)malloc(sizeof(tokenlist));
        ts->next=NULL;
        t=ts;
        do
        {
            buffer B;
            r=getStream(fp,B,k);
            for(i=0; i<SIZE_BUFFER; i++)
            {
                if(0<=i<SIZE_BUFFER)
                {
                    c=B[i];
                }
                switch(s)
                {
                case -2:
                {
                    c=d;
                    s=0;
                }
                case 0:
                {
                    if(c=='$')
                    {
                        x=1;
                        t->lineno=-1;
                        break;
                    }
                    else if(c=='%')
                    {
                        s=50;
                        break;
                    }
                    else if(c==' ' || c=='\t')
                    {
                        break;
                    }
                    else if(c=='\n')
                    {
                        ln++;
                        break;

                    }
                    else if(c==',')
                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]=',';
                        t->token="TK_COMMA";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }
                    else if(c=='[')
                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]='[';
                        t->token="TK_SQL";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }
                    else if(c==']')
                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]=']';
                        t->token="TK_SQR";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }
                    else if(c==';')
                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]=';';
                        t->token="TK_SEM";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }
                    else if(c==':')
                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]=':';
                        t->token="TK_COLON";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }
                    else if(c=='.')
                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]='.';
                        t->token="TK_DOT";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }
                    else if(c=='(')

                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]='(';
                        t->token="TK_OP";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }

                    else if(c==')')
                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]=')';
                        t->token="TK_CL";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }

                    else if(c=='+')

                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]='+';
                        t->token="TK_PLUS";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }

                    else if(c=='-')

                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]='-';
                        t->token="TK_MINUS";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }

                    else if(c=='*')

                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]='*';
                        t->token="TK_MUL";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }
                    else if(c=='/')
                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]='/';
                        t->token="TK_DIV";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }

                    else if(c=='&')
                    {
                        id[l]=c;
                        s=12;
                        break;
                    }
                    else if(c=='@')
                    {
                        id[l]=c;
                        s=13;
                        break;
                    }
                    else if(c=='~')

                    {
                        t->lineno=ln;

                        flush(t->lexeme);
                        t->lexeme[0]='~';

                        t->token="TK_NOT";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        s=0;
                        break;
                    }

                    else if(c=='=')
                    {
                        id[l]=c;
                        s=15;
                        break;
                    }
                    else if(c=='!')
                    {
                        id[l]=c;
                        s=16;
                        break;
                    }
                    else if(c=='#')
                    {
                        s=18;
                        id[l]=c;
                        break;
                    }
                    else if(c=='<')
                    {
                        id[l]=c;
                        s=17;
                        break;
                    }

                    else if(c=='>')
                    {
                        id[l]=c;
                        s=20;
                        break;
                    }
                    else if('0'<=c && c<='9')
                    {
                        s=19;
                        id[l]=c;//INCOMPLETE
                        break;
                    }
                    else if(c=='_')
                    {
                        id[l]=c;
                        s=21;
                        break;
                    }
                    else if('b'<=c && c<='d')
                    {
                        id[l]=c;
                        s=35;
                        break;
                    }
                    else if(c=='a' || 'e'<=c && c<='z')
                    {
                        id[l]=c;
                        s=36;
                        break;
                    }
                    else
                    {
                        printf("ERROR_2: Unknown Symbol %c at line %d\n",c,ln);
                        s=0;
                        break;
                    }
                }
                case 50:
                {
                    if(c=='\n' || c=='$')
                    {
                        t->lineno=ln;

                        flush(t->lexeme);
                        t->lexeme[0]='%';

                        t->token="TK_COMMENT";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        ln++;
                        s=0;
                        break;
                    }
                    else
                    {
                        s=50;
                        break;
                    }
                }

                case 12:
                {

                    if(c=='&')
                    {
                        l++;
                        id[l]=c;
                        s=23;
                        break;
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }
                }
                case 23:
                {
                    if(c=='&')
                    {
                        l++;
                        id[l]=c;
                        t->lineno=ln;
                        strcpy(t->lexeme,id);
                        t->token="TK_AND";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        s=0;
                        break;
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }
                }
                case 13:
                {

                    if(c=='@')
                    {
                        l++;
                        id[l]=c;
                        s=24;
                        break;
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }
                }
                case 24:
                {
                    if(c=='@')
                    {
                        l++;
                        id[l]=c;
                        t->lineno=ln;

                        strcpy(t->lexeme,id);
                        t->token="TK_OR";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        s=0;
                        break;
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }
                }
                case 15:
                {
                    if(c=='=')
                    {
                        l++;
                        id[l]=c;
                        t->lineno=ln;
                        strcpy(t->lexeme,id);
                        t->token="TK_EQ";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        s=0;
                        break;
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }
                }
                case 16:
                {
                    if(c=='=')
                    {
                        l++;
                        id[l]=c;
                        t->lineno=ln;

                        strcpy(t->lexeme,id);
                        t->token="TK_NE";

                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        s=0;
                        break;
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }
                }
                case 17:
                {
                    if(c=='=')
                    {
                        l++;
                        id[l]=c;
                        t->lineno=ln;

                        strcpy(t->lexeme,id);
                        t->token="TK_LE";

                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        s=0;
                        break;
                    }
                    if(c=='-')
                    {
                        l++;
                        id[l]=c;
                        s=25;
                        break;
                    }
                    else
                    {

                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]='<';
                        t->token="TK_LT";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        i--;
                        d=c;
                        s=0;
                        break;
                    }
                }
                case 25:
                {

                    if(c=='-')
                    {
                        l++;
                        id[l]=c;
                        s=26;
                        break;
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }
                }
                case 26:
                {

                    if(c=='-')
                    {
                        l++;
                        id[l]=c;
                        t->lineno=ln;

                        strcpy(t->lexeme,id);
                        t->token="TK_ASSIGNOP";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;

                        l=0;
                        flush(id);
                        s=0;
                        break;
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }
                }
                case 20:
                {
                    if(c=='=')
                    {
                        l++;
                        id[l]=c;
                        t->lineno=ln;

                        strcpy(t->lexeme,id);
                        t->token="TK_GE";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        s=0;
                        break;
                    }
                    else
                    {
                        t->lineno=ln;
                        flush(t->lexeme);
                        t->lexeme[0]='>';
                        t->token="TK_GT";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        i--;
                        d=c;
                        s=0;
                        break;
                    }
                }
                case 18:
                {
                    if('a'<=c && c<'=z')
                    {
                        l++;
                        id[l]=c;
                        s=27;
                        break;
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }
                }
                case 27:
                {
                    if('a'<=c && c<'=z')
                    {
                        l++;
                        if(l<20)
                        {
                            id[l]=c;
                            break;
                        }
                        else
                        {
                            s=31;
                            break;
                        }
                    }
                    else
                    {
                        t->lineno=ln;

                        strcpy(t->lexeme,id);

                        t->token="TK_RECORDID";

                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        i--;

                        s=0;
                        break;
                    }
                }

                case 19:
                {
                    //DO NUM AND RNUM
                    if('0'<=c && c<='9')
                    {
                        l++;
                        if(l<20)
                        {
                            id[l]=c;
                            break;
                        }
                        else
                        {
                            s=41;
                            break;
                        }
                    }
                    else if(c=='.')
                    {
                        l++;
                        if(l<18)
                        {
                            id[l]=c;
                            s=30;
                            break;
                        }
                        else
                        {
                            id[l]=c;
                            s=39;
                            break;
                        }
                    }
                    else
                    {
                        t->lineno=ln;

                        strcpy(t->lexeme,id);

                        t->token="TK_NUM";

                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        i--;

                        s=0;
                        break;
                    }
                }
                case 30:
                {
                    if('0'<=c && c<='9')
                    {
                        l++;
                        if(l<19)
                        {
                            id[l]=c;
                            s=34;
                            break;
                        }
                        else
                        {
                            id[l]=c;
                            s=39;
                            break;
                        }
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }
                }
                case 34:
                {
                    if('0'<=c && c<='9')
                    {
                        l++;
                        id[l]=c;
                        t->lineno=ln;

                        strcpy(t->lexeme,id);

                        t->token="TK_RNUM";

                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        //i--;

                        s=0;
                        break;
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }
                }
                case 39:
                {
                    if('0'<=c && c<='9')
                    {
                        l++;
                        if(l<20)
                        {
                            id[l]=c;
                            break;
                        }
                        else
                        {
                            s=41;
                            break;
                        }
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }

                }
                case 21:
                {
                    if('a'<=c && c<'=z' || 'A'<=c && c<='Z')
                    {
                        l++;
                        id[l]=c;
                        s=28;
                        break;
                    }
                    else
                    {
                        s=100;
                        d=c;
                        break;
                    }
                }
                case 28:
                {
                    if('a'<=c && c<'=z' || 'A'<=c && c<='Z')
                    {
                        l++;
                        if(l<20)
                        {
                            id[l]=c;
                            break;
                        }
                        else
                        {
                            s=42;
                            break;
                        }
                    }
                    else if('0'<=c && c<='9')
                    {
                        s=29;
                    }
                    else
                    {
                        t->lineno=ln;

                        strcpy(t->lexeme,id);

                        t->token="TK_FUNID";

                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        i--;

                        s=0;
                        break;
                    }
                }
                case 29:
                {
                    if('0'<=c && c<='9')
                    {
                        l++;
                        if(l<20)
                        {
                            id[l]=c;
                            break;
                        }
                        else
                        {
                            s=41;
                            break;
                        }
                    }
                    else
                    {
                        t->lineno=ln;
                        strcpy(t->lexeme,id);
                        t->token="TK_FUNID";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        i--;

                        s=0;
                        break;
                    }
                }

                case 35:
                {
                    if('2'<=c && c<='7')
                    {
                        l++;
                        id[l]=c;
                        s=37;
                        break;
                    }
                    else if('a'<=c && c<='z')
                    {
                        l++;
                        id[l]=c;
                        s=36;
                        break;
                    }
                    else
                    {
                        t->lineno=ln;
                        strcpy(t->lexeme,id);
                        t->token="TK_FIELDID";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        i--;
                        s=0;
                        break;
                    }
                }
                case 36:
                {
                    if('a'<=c && c<'=z')
                    {
                        l++;
                        if(l<20)
                        {
                            id[l]=c;
                            break;
                        }
                        else
                        {
                            s=31;
                            break;
                        }
                    }
                    else
                    {
                        t->lineno=ln;
                        strcpy(t->lexeme,id);
                        t->token="TK_FIELDID";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        i--;

                        s=0;
                        break;
                    }
                }
                case 37:
                {
                    if('b'<=c && c<='d')
                    {
                        l++;
                        if(l<20)
                        {
                            id[l]=c;
                            break;
                        }
                        else
                        {
                            s=43;
                            break;
                        }
                    }
                    else if('2'<=c && c<='7')
                    {
                        s=38;
                    }
                    else
                    {
                        t->lineno=ln;
                        strcpy(t->lexeme,id);
                        t->token="TK_ID";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        i--;

                        s=0;
                        break;
                    }
                }
                case 38:
                {
                    if('2'<=c && c<='7')
                    {
                        l++;
                        if(l<20)
                        {
                            id[l]=c;
                            break;
                        }
                        else
                        {
                            s=44;
                            break;
                        }
                    }
                    else
                    {
                        t->lineno=ln;

                        strcpy(t->lexeme,id);

                        t->token="TK_ID";
                        t->next=(tokenInfo)malloc(sizeof(tokenlist));
                        t=t->next;
                        t->lineno=-1;
                        t->next=NULL;
                        l=0;
                        flush(id);
                        i--;
                        s=0;
                        break;
                    }
                }
                case 31:
                {
                    if('a'<=c && c<'=z')
                    {
                        break;
                    }
                    else
                    {
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",ln);
                        l=0;
                        flush(id);
                        i--;

                        d=c;
                        s=0;
                        break;
                    }
                }

                case 41:
                {
                    if('0'<=c && c<='9')
                    {
                        break;
                    }
                    else
                    {
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",ln);
                        l=0;
                        flush(id);
                        i--;

                        d=c;
                        s=0;
                        break;
                    }
                }

                case 42:
                {
                    if('a'<=c && c<'=z' || 'A'<=c && c<='Z')
                    {
                        break;
                    }
                    else
                    {
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",ln);
                        l=0;
                        flush(id);
                        i--;

                        d=c;
                        s=0;
                        break;
                    }
                }

                case 43:
                {
                    if('b'<=c && c<='d')
                    {
                        break;
                    }
                    else
                    {
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",ln);
                        l=0;
                        flush(id);
                        i--;

                        d=c;
                        s=0;
                        break;
                    }
                }
                case 44:
                {
                    if('2'<=c && c<='7')
                    {
                        break;
                    }
                    else
                    {
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",ln);
                        l=0;
                        flush(id);
                        i--;

                        d=c;
                        s=0;
                        break;
                    }
                }
                case 100:
                {
                    printf("ERROR_3: Unknown pattern <%s> at line number <%d>\n",id,ln);
                    l=0;
                    flush(id);
                    if(i==0)
                    {
                        s=-2;
                        i=-2;
                        break;
                    }
                    else i=i-2;
                    s=0;
                    break;

                }
                }
                if(x==1)
                {
                    break;
                }
            }
            if(temp==1 || x==1)
            {
                break;
            }
        }
        while(!feof(r.fp));
        tl=ts;
        char *A="TK_FUNID";
        char *Z="TK_FIELDID";
        while(tl->lineno!=-1)
        {
            if(strcmp(tl->token,A)==0)
            {
                char* C="_main";
                else if(strcmp(tl->lexeme,C)==0)
                {
                    tl->token="TK_MAIN";
                }
            }
            else if(strcmp(tl->token,Z)==0)
            {
                char* C="with";
                char* D="parameters";
                char* E="end";
                char* F="while";
                char* G="int";
                char* H="real";
                char* I="type";
                char* J="global";
                char* K="parameter";
                char* L="list";
                char* M="input";
                char* N="output";
                char* O="endwhile";
                char* P="if";
                char* Q="then";
                char* R="endif";
                char* S="read";
                char* T="write";
                char* U="return";
                char* V="call";
                char* W="record";
                char* X="endrecord";
                char* Y="else";
                if(strcmp(tl->lexeme,C)==0)
                {
                    tl->token="TK_WITH";
                }
                else if(strcmp(tl->lexeme,D)==0)
                {
                    tl->token="TK_PARAMETERS";
                }
                else if(strcmp(tl->lexeme,E)==0)
                {
                    tl->token="TK_END";
                }
                else if(strcmp(tl->lexeme,F)==0)
                {
                    tl->token="TK_WHILE";
                }
                else if(strcmp(tl->lexeme,G)==0)
                {
                    tl->token="TK_INT";
                }
                else if(strcmp(tl->lexeme,H)==0)
                {
                    tl->token="TK_REAL";
                }
                else if(strcmp(tl->lexeme,I)==0)
                {
                    tl->token="TK_TYPE";
                }
                else if(strcmp(tl->lexeme,J)==0)
                {
                    tl->token="TK_GLOBAL";
                }
                else if(strcmp(tl->lexeme,K)==0)
                {
                    tl->token="TK_PARAMETER";
                }
                else if(strcmp(tl->lexeme,L)==0)
                {
                    tl->token="TK_LIST";
                }
                else if(strcmp(tl->lexeme,M)==0)
                {
                    tl->token="TK_INPUT";
                }
                else if(strcmp(tl->lexeme,N)==0)
                {
                    tl->token="TK_OUTPUT";
                }
                else if(strcmp(tl->lexeme,O)==0)
                {
                    tl->token="TK_ENDWHILE";
                }
                else if(strcmp(tl->lexeme,P)==0)
                {
                    tl->token="TK_IF";
                }
                else if(strcmp(tl->lexeme,Q)==0)
                {
                    tl->token="TK_THEN";
                }
                else if(strcmp(tl->lexeme,R)==0)
                {
                    tl->token="TK_ENDIF";
                }
                else if(strcmp(tl->lexeme,S)==0)
                {
                    tl->token="TK_READ";
                }
                else if(strcmp(tl->lexeme,T)==0)
                {
                    tl->token="TK_WRITE";
                }
                else if(strcmp(tl->lexeme,U)==0)
                {
                    tl->token="TK_RETURN";
                }
                else if(strcmp(tl->lexeme,V)==0)
                {
                    tl->token="TK_CALL";
                }
                else if(strcmp(tl->lexeme,W)==0)
                {
                    tl->token="TK_RECORD";
                }
                else if(strcmp(tl->lexeme,X)==0)
                {
                    tl->token="TK_ENDRECORD";
                }
                else if(strcmp(tl->lexeme,Y)==0)
                {
                    tl->token="TK_ELSE";
                }

            }
            tl=tl->next;
        }
        t=ts;
        return ts;
    }
    else
    {
        t=t->next;
        return t;
    }
}

void printTokenlist(char *cp)
{
    FILE *fin=fopen(cp,"r");
    FILE *fout=fopen("output.txt","w");
    if(fin==NULL)
    {
        fprintf(fout,"Error opening the file\n");
        return 0;
    }
    else
    {
    }
    tokenInfo info;
    info=NULL;
    info=getNextToken(fin,SIZE_BUFFER,info);

    while(info->lineno!=-1)
    {
        fprintf(fout,"%d %s %s\n",info->lineno,info->lexeme,info->token);
        printf("%d %s %s\n",info->lineno,info->lexeme,info->token);
        info=getNextToken(fin,SIZE_BUFFER,info);

    }
    info=NULL;
    rewind(fin);
    fclose(fin);
    return;
}


