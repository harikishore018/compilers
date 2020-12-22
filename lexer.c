/*
2017A7PS0133P M VENKAT SAI RAM
2017A7PS0079P ABHISHEK BHARADWAJ
2017A7PS0144P K SAI KISHORE
2017A7PS0141P B HARI KISHORE
2017A7PS0154P G SAI SARATH KRISHNA

GROUP NUMBER 45
*/
#include "lexer.h"
TABLE hashTable[TABLE_SIZE];  
int line_num=1;
int *line_tok;
int line_count;
LEXER **tok_arr;
int tok_arr_size;

int isNum(char ch)
{
    if((ch>=48)&&(ch<=57))
        return 1;
    else
        return 0;
    
}

// **************************************************************************************************

int isAlphabet(char ch)
{
    if(((ch>=65)&&(ch<=90)) || ((ch>=97)&&(ch<=122)))
        return 1;
    else
        return 0;    
}

// **************************************************************************************************

void reportError(char *lex)
{
    	printf(" Line no. %d : INVALID LEXEME \"%s\" \n",line_num,lex);
}

// **************************************************************************************************

void insertKeywords()
{
    SYM_ENTRY *keywords=(SYM_ENTRY *)malloc(sizeof(SYM_ENTRY)*33);
    keywords[0].lexeme=(char *)malloc(sizeof(char)*8);
    keywords[0].token=(char *)malloc(sizeof(char)*8);
    keywords[0].lexeme=strcpy(keywords[0].lexeme,"integer");
    keywords[0].token=strcpy(keywords[0].token,"INTEGER");
    keywords[0].next=NULL;
    insert(&keywords[0]);

    keywords[1].lexeme=(char *)malloc(sizeof(char)*5);
    keywords[1].token=(char *)malloc(sizeof(char)*5);
    keywords[1].lexeme=strcpy(keywords[1].lexeme,"real");
    keywords[1].token=strcpy(keywords[1].token,"REAL");
    keywords[1].next=NULL;
    insert(&keywords[1]);

    keywords[2].lexeme=(char *)malloc(sizeof(char)*8);
    keywords[2].token=(char *)malloc(sizeof(char)*8);
    keywords[2].lexeme=strcpy(keywords[2].lexeme,"boolean");
    keywords[2].token=strcpy(keywords[2].token,"BOOLEAN");
    keywords[2].next=NULL;
    insert(&keywords[2]);

    keywords[3].lexeme=(char *)malloc(sizeof(char)*3);
    keywords[3].token=(char *)malloc(sizeof(char)*3);
    keywords[3].lexeme=strcpy(keywords[3].lexeme,"of");
    keywords[3].token=strcpy(keywords[3].token,"OF");
    keywords[3].next=NULL;
    insert(&keywords[3]);

    keywords[4].lexeme=(char *)malloc(sizeof(char)*6);
    keywords[4].token=(char *)malloc(sizeof(char)*6);
    keywords[4].lexeme=strcpy(keywords[4].lexeme,"array");
    keywords[4].token=strcpy(keywords[4].token,"ARRAY");
    keywords[4].next=NULL;
    insert(&keywords[4]);

    keywords[5].lexeme=(char *)malloc(sizeof(char)*6);
    keywords[5].token=(char *)malloc(sizeof(char)*6);
    keywords[5].lexeme=strcpy(keywords[5].lexeme,"start");
    keywords[5].token=strcpy(keywords[5].token,"START");
    keywords[5].next=NULL;
    insert(&keywords[5]);

    keywords[6].lexeme=(char *)malloc(sizeof(char)*4);
    keywords[6].token=(char *)malloc(sizeof(char)*4);
    keywords[6].lexeme=strcpy(keywords[6].lexeme,"end");
    keywords[6].token=strcpy(keywords[6].token,"END");
    keywords[6].next=NULL;
    insert(&keywords[6]);

    keywords[7].lexeme=(char *)malloc(sizeof(char)*8);
    keywords[7].token=(char *)malloc(sizeof(char)*8);
    keywords[7].lexeme=strcpy(keywords[7].lexeme,"declare");
    keywords[7].token=strcpy(keywords[7].token,"DECLARE");
    keywords[7].next=NULL;
    insert(&keywords[7]);

    keywords[8].lexeme=(char *)malloc(sizeof(char)*7);
    keywords[8].token=(char *)malloc(sizeof(char)*7);
    keywords[8].lexeme=strcpy(keywords[8].lexeme,"module");
    keywords[8].token=strcpy(keywords[8].token,"MODULE");
    keywords[8].next=NULL;
    insert(&keywords[8]);

    keywords[9].lexeme=(char *)malloc(sizeof(char)*7);
    keywords[9].token=(char *)malloc(sizeof(char)*7);
    keywords[9].lexeme=strcpy(keywords[9].lexeme,"driver");
    keywords[9].token=strcpy(keywords[9].token,"DRIVER");
    keywords[9].next=NULL;
    insert(&keywords[9]);

    keywords[10].lexeme=(char *)malloc(sizeof(char)*8);
    keywords[10].token=(char *)malloc(sizeof(char)*8);
    keywords[10].lexeme=strcpy(keywords[10].lexeme,"program");
    keywords[10].token=strcpy(keywords[10].token,"PROGRAM");
    keywords[10].next=NULL;
    insert(&keywords[10]);

    keywords[11].lexeme=(char *)malloc(sizeof(char)*10);
    keywords[11].token=(char *)malloc(sizeof(char)*10);
    keywords[11].lexeme=strcpy(keywords[11].lexeme,"get_value");
    keywords[11].token=strcpy(keywords[11].token,"GET_VALUE");
    keywords[11].next=NULL;
    insert(&keywords[11]);

    keywords[12].lexeme=(char *)malloc(sizeof(char)*6);
    keywords[12].token=(char *)malloc(sizeof(char)*6);
    keywords[12].lexeme=strcpy(keywords[12].lexeme,"print");
    keywords[12].token=strcpy(keywords[12].token,"PRINT");
    keywords[12].next=NULL;
    insert(&keywords[12]);

    keywords[13].lexeme=(char *)malloc(sizeof(char)*4);
    keywords[13].token=(char *)malloc(sizeof(char)*4);
    keywords[13].lexeme=strcpy(keywords[13].lexeme,"use");
    keywords[13].token=strcpy(keywords[13].token,"USE");
    keywords[13].next=NULL;
    insert(&keywords[13]);

    keywords[14].lexeme=(char *)malloc(sizeof(char)*5);
    keywords[14].token=(char *)malloc(sizeof(char)*5);
    keywords[14].lexeme=strcpy(keywords[14].lexeme,"with");
    keywords[14].token=strcpy(keywords[14].token,"WITH");
    keywords[14].next=NULL;
    insert(&keywords[14]);

    keywords[15].lexeme=(char *)malloc(sizeof(char)*11);
    keywords[15].token=(char *)malloc(sizeof(char)*11);
    keywords[15].lexeme=strcpy(keywords[15].lexeme,"parameters");
    keywords[15].token=strcpy(keywords[15].token,"PARAMETERS");
    keywords[15].next=NULL;
    insert(&keywords[15]);

    keywords[16].lexeme=(char *)malloc(sizeof(char)*5);
    keywords[16].token=(char *)malloc(sizeof(char)*5);
    keywords[16].lexeme=strcpy(keywords[16].lexeme,"true");
    keywords[16].token=strcpy(keywords[16].token,"TRUE");
    keywords[16].next=NULL;
    insert(&keywords[16]);

    keywords[17].lexeme=(char *)malloc(sizeof(char)*6);
    keywords[17].token=(char *)malloc(sizeof(char)*6);
    keywords[17].lexeme=strcpy(keywords[17].lexeme,"false");
    keywords[17].token=strcpy(keywords[17].token,"FALSE");
    keywords[17].next=NULL;
    insert(&keywords[17]);

    keywords[18].lexeme=(char *)malloc(sizeof(char)*6);
    keywords[18].token=(char *)malloc(sizeof(char)*6);
    keywords[18].lexeme=strcpy(keywords[18].lexeme,"takes");
    keywords[18].token=strcpy(keywords[18].token,"TAKES");
    keywords[18].next=NULL;
    insert(&keywords[18]);

    keywords[19].lexeme=(char *)malloc(sizeof(char)*6);
    keywords[19].token=(char *)malloc(sizeof(char)*6);
    keywords[19].lexeme=strcpy(keywords[19].lexeme,"input");
    keywords[19].token=strcpy(keywords[19].token,"INPUT");
    keywords[19].next=NULL;
    insert(&keywords[19]);

    keywords[20].lexeme=(char *)malloc(sizeof(char)*8);
    keywords[20].token=(char *)malloc(sizeof(char)*8);
    keywords[20].lexeme=strcpy(keywords[20].lexeme,"returns");
    keywords[20].token=strcpy(keywords[20].token,"RETURNS");
    keywords[20].next=NULL;
    insert(&keywords[20]);

    keywords[21].lexeme=(char *)malloc(sizeof(char)*4);
    keywords[21].token=(char *)malloc(sizeof(char)*4);
    keywords[21].lexeme=strcpy(keywords[21].lexeme,"AND");
    keywords[21].token=strcpy(keywords[21].token,"AND");
    keywords[21].next=NULL;
    insert(&keywords[21]);

    keywords[22].lexeme=(char *)malloc(sizeof(char)*3);
    keywords[22].token=(char *)malloc(sizeof(char)*3);
    keywords[22].lexeme=strcpy(keywords[22].lexeme,"OR");
    keywords[22].token=strcpy(keywords[22].token,"OR");
    keywords[22].next=NULL;
    insert(&keywords[22]);

    keywords[23].lexeme=(char *)malloc(sizeof(char)*4);
    keywords[23].token=(char *)malloc(sizeof(char)*4);
    keywords[23].lexeme=strcpy(keywords[23].lexeme,"for");
    keywords[23].token=strcpy(keywords[23].token,"FOR");
    keywords[23].next=NULL;
    insert(&keywords[23]);

    keywords[24].lexeme=(char *)malloc(sizeof(char)*3);
    keywords[24].token=(char *)malloc(sizeof(char)*3);
    keywords[24].lexeme=strcpy(keywords[24].lexeme,"in");
    keywords[24].token=strcpy(keywords[24].token,"IN");
    keywords[24].next=NULL;
    insert(&keywords[24]);

    keywords[25].lexeme=(char *)malloc(sizeof(char)*7);
    keywords[25].token=(char *)malloc(sizeof(char)*7);
    keywords[25].lexeme=strcpy(keywords[25].lexeme,"switch");
    keywords[25].token=strcpy(keywords[25].token,"SWITCH");
    keywords[25].next=NULL;
    insert(&keywords[25]);

    keywords[26].lexeme=(char *)malloc(sizeof(char)*5);
    keywords[26].token=(char *)malloc(sizeof(char)*5);
    keywords[26].lexeme=strcpy(keywords[26].lexeme,"case");
    keywords[26].token=strcpy(keywords[26].token,"CASE");
    keywords[26].next=NULL;
    insert(&keywords[26]);


    keywords[27].lexeme=(char *)malloc(sizeof(char)*6);
    keywords[27].token=(char *)malloc(sizeof(char)*6);
    keywords[27].lexeme=strcpy(keywords[27].lexeme,"break");
    keywords[27].token=strcpy(keywords[27].token,"BREAK");
    keywords[27].next=NULL;
    insert(&keywords[27]);

    keywords[28].lexeme=(char *)malloc(sizeof(char)*8);
    keywords[28].token=(char *)malloc(sizeof(char)*8);
    keywords[28].lexeme=strcpy(keywords[28].lexeme,"default");
    keywords[28].token=strcpy(keywords[28].token,"DEFAULT");
    keywords[28].next=NULL;
    insert(&keywords[28]);

    keywords[29].lexeme=(char *)malloc(sizeof(char)*6);
    keywords[29].token=(char *)malloc(sizeof(char)*6);
    keywords[29].lexeme=strcpy(keywords[29].lexeme,"while");
    keywords[29].token=strcpy(keywords[29].token,"WHILE");
    keywords[29].next=NULL;
    insert(&keywords[29]);
}

// **************************************************************************************************

void removeComments(FILE *fp1,FILE *cleanFile)
{

    char ch;
    char *buf=(char *)malloc(1);
    int buf_count=1;
    int star_count=0;
    int line_count=0;
    while((ch=fgetc(fp1))!=EOF)
    {
        if(ch=='*')
        {
            if(((ch=fgetc(fp1))!=EOF) && (ch!='*'))
                fprintf(cleanFile,"*%c",ch);
            else if((ch!=EOF) && (ch=='*'))
            {
                    while((ch=fgetc(fp1))!=EOF)
                    {
                        buf_count++;
                        buf=(char *)realloc(buf,buf_count);
                        buf[buf_count-2]=ch;
                        if(ch=='\n')
                            line_count++;          
 // buf_count contains the amount of memory in the buffer and no. of characters stored=buf_count-1
                        if(ch=='*')
                        {
                            if(((ch=fgetc(fp1))!=EOF) && (ch=='*'))
                            {
                                 for (int i=0;i<(buf_count-1);i++)
                                 {
		                     if(buf[i]=='\n')
			                 fprintf(cleanFile,"\n");
			             else
			                 fprintf(cleanFile," ");		
                                     //fprintf(cleanFile,"\n");
                                    line_count=0;
                                }	                                
				free(buf);
                                buf=(char *)malloc(1);
                                buf_count=1;
                                break;
                            }
                            else if((ch!=EOF) && (ch!='*'))
                            {
                                if(ch=='\n')
                                    line_count++;
                                buf_count++;
                                buf=(char *)realloc(buf,buf_count);
                                buf[buf_count-2]=ch;
                                continue;
                            }
                            else
                                break;
                            continue;
                        }
                    }
                    if(buf_count!=1)
                    {
                        fprintf(cleanFile,"**");
                        for(int i=0;i<buf_count-1;i++)
                            fprintf(cleanFile,"%c",buf[i]);
                    }
                    if((buf_count==1)&&(ch==EOF))
                        fprintf(cleanFile,"**");
                    if((buf_count==1)&&(ch=='*'))
                    {
                        
                    }
            }
            else
                fprintf(cleanFile,"*");
        }
        else
            fprintf(cleanFile,"%c",ch);
    }
    fseek(fp1,0,SEEK_SET);
}


int commentFinder(FILE *fp)
{
    char ch;
    int i=0;
    while((ch=fgetc(fp))!=EOF)
    {
        //printf("\n\n %c\n",ch);
        i--;
        if(ch=='*')
        {
            if((ch=fgetc(fp))=='*')
            {   
                i--;
                fseek(fp,i,SEEK_CUR);
                return 1;
            }
            if(ch==EOF)
            {   
                i--;
                fseek(fp,i,SEEK_CUR); 
                return 0;       
            }
            i--;
        }
    }
    fseek(fp,i,SEEK_CUR);
    return 0;
}

// **************************************************************************************************

BLOCK *getStream(BLOCK *bl)
{
    char ch;
    FILE *fp1=bl->fp;
    FILE *fp1_cpy=NULL;
    int cmnt_num=1;
    char *buf=NULL;
    bl->len=0;
    while((ch=fgetc(fp1))!=EOF)
    {
        if(ch=='\n')
        {
            buf=realloc(buf,(bl->len)+2);
	    buf[(bl->len)+1]='\0';
            buf[bl->len]=ch;
            bl->len++;
            bl->stream=buf;
            return bl;
        }
        else if((ch=='*')&&(cmnt_num==1))
        {
            //printf("\n first \n");
            if(((ch=fgetc(fp1))!=EOF)&&(ch=='*'))
            {
               // printf("second");
                //printf("%d",commentFinder(fp1));

                if(commentFinder(fp1))
                {
                    //printf("\n NENE RA %d\n",commentFinder(fp1));
                    buf=realloc(buf,(bl->len)+2);
                    buf[bl->len]=buf[(bl->len)+1]=' ';
                    (bl->len)+=2;
                    while(1)
                    {
                        ch=fgetc(fp1);
		        buf=realloc(buf,(bl->len)+1);
                        if(ch=='\n')
                            buf[bl->len]='\n';
                        else
			    buf[bl->len]=' ';
                        bl->len++;
                        //printf("\n%c\n",ch);
                        if(ch=='*')
                        {
                            ch=fgetc(fp1);
                            buf=realloc(buf,(bl->len)+1);
                            if(ch=='\n')
                                buf[bl->len]='\n';
                            else
			        buf[bl->len]=' ';
                            bl->len++;
                           // printf("\n%c\n",ch);
                            if(ch=='*')
                            {
				buf=realloc(buf,(bl->len)+1);
				buf[bl->len]='\0';		
                                bl->stream=buf;
                                return bl;   
                            }
                        }     
                    } 
                    //printf("\n sexy boi\n");
                }
                else
                {
                    buf=realloc(buf,(bl->len)+2);
                    buf[bl->len]=buf[(bl->len)+1]='*';
                    cmnt_num=0;
                }
            }
            else if((ch!=EOF)&&(ch=='\n'))
            {
                buf=realloc(buf,(bl->len)+3);
                buf[bl->len]='*';
                buf[(bl->len)+1]=ch;
          	buf[(bl->len)+2]='\0';
                (bl->len)+=2;  
                bl->stream=buf;
                return bl;
            }
            else if(ch==EOF)
            {
                buf=realloc(buf,(bl->len)+2);
		buf[(bl->len)+1]='\0';
                buf[bl->len]='*';
                bl->len++;
                bl->stream=buf;
                return bl;
            }    
            else
            {
                //printf("\nboi\n");
                buf=realloc(buf,(bl->len)+3);
		buf[(bl->len)+2]='\0';
                buf[(bl->len)+1]=ch;
                buf[bl->len]='*';
                bl->len+=2;   
            }  
        }
        else
        {
            buf=realloc(buf,(bl->len)+1);
            buf[bl->len]=ch;
            bl->len++;
        }  
    }
    buf=realloc(buf,(bl->len)+1);
    buf[bl->len]='\0';
    bl->stream=buf;
    return bl;
}

// **************************************************************************************************

LEXER *getNextToken(BLOCK *bl)       // append '\0' to bl->buf in getStream
{
    char *tok=NULL;
    char *lex=NULL;
    BLOCK *bl_cpy=NULL;
    int sym_count=0,i=0;
    LEXER *lr=NULL;
    while(1)
    {
        i=0;
    	if((bl->stream)[0]=='+')
    	{
                tok=(char *)calloc(5,sizeof(char));
                tok=strcpy(tok,"PLUS");
		    (bl->stream)++;
                printf(" Line no. %d < %s , %s > \n",line_num,"+",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"+");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
    	}
	else if((bl->stream)[0]=='-')
    	{
                tok=(char *)calloc(6,sizeof(char));
                tok=strcpy(tok,"MINUS");
                (bl->stream)++;
                 printf(" Line no. %d < %s , %s > \n",line_num,"-",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"-");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;		    
    	}
   	else if((bl->stream)[0]=='*')
   	{
                if((bl->stream)[1]!='*')
                {
                    tok=(char *)calloc(4,sizeof(char));
                    tok=strcpy(tok,"MUL");
                    (bl->stream)++;
                    printf(" Line no. %d < %s , %s > \n",line_num,"*",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"*");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }

    	}
    	else if((bl->stream)[0]=='/')
    	{
                tok=(char *)calloc(4,sizeof(char));
                tok=strcpy(tok,"DIV");
                (bl->stream)++;
                printf(" Line no. %d < %s , %s > \n",line_num,"/",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"/");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
    	}
    	else if((bl->stream)[0]=='<')
    	{
                if(((bl->stream)[1]=='<')&&((bl->stream)[2]=='<'))
                {
                    tok=(char *)calloc(10,sizeof(char));
                    tok=strcpy(tok,"DRIVERDEF");
                    (bl->stream)+=3;
                    printf(" Line no. %d < %s , %s > \n",line_num,"<<<",tok);
                lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(4,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"<<<");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }
                else if(((bl->stream)[1]=='<')&&((bl->stream)[2]!='<'))
                {
                    tok=(char *)calloc(4,sizeof(char));
                    tok=strcpy(tok,"DEF");
                    (bl->stream)+=2;
                    printf(" Line no. %d < %s , %s > \n",line_num,"<<",tok);
                   lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(3,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"<<");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }
                else if((bl->stream)[1]=='=')
                {
                    tok=(char *)calloc(3,sizeof(char));
                    tok=strcpy(tok,"LE");
                    (bl->stream)+=2;
                    printf(" Line no. %d < %s , %s > \n",line_num,"<=",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(3,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"<=");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }
                else
                {
                    tok=(char *)calloc(3,sizeof(char));
                    tok=strcpy(tok,"LT");
                    (bl->stream)+=1;
                    printf(" Line no. %d < %s , %s > \n",line_num,"<",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"<");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }
            
   	}
    	else if((bl->stream)[0]=='>')
    	{
                if(((bl->stream)[1]=='>')&&((bl->stream)[2]=='>'))
                {
                    tok=(char *)calloc(13,sizeof(char));
                    tok=strcpy(tok,"DRIVERENDDEF");
                    (bl->stream)+=3;
                    printf(" Line no. %d < %s , %s > \n",line_num,">>>",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(4,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,">>>");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }
                else if(((bl->stream)[1]=='>')&&((bl->stream)[2]!='>'))
                {
                    tok=(char *)calloc(7,sizeof(char));
                    tok=strcpy(tok,"ENDDEF");
                    (bl->stream)+=2;
                    printf(" Line no. %d < %s , %s > \n",line_num,">>",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(3,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,">>");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }
                else if((bl->stream)[1]=='=')
                {
                    tok=(char *)calloc(3,sizeof(char));
                    tok=strcpy(tok,"GE");
                    (bl->stream)+=2;
                    printf(" Line no. %d < %s , %s > \n",line_num,">=",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(3,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,">=");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }
                else
                {
                    tok=(char *)calloc(3,sizeof(char));
                    tok=strcpy(tok,"GT");
                    (bl->stream)+=1;
                    printf(" Line no. %d < %s , %s > \n",line_num,">",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,">");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }
	 }
    	 else if((bl->stream)[0]=='=')
   	 {
                if((bl->stream)[1]=='=')
                {
                    tok=(char *)calloc(3,sizeof(char));
                    tok=strcpy(tok,"EQ");
                    (bl->stream)+=2;
                    printf(" Line no. %d < %s , %s > \n",line_num,"==",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(3,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"==");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }   
                else
                {
			(bl->stream)++;		
			reportError("=");
			//break;
		}
    	}
    	else if((bl->stream)[0]=='!')
    	{
                if((bl->stream)[1]=='=')
                {
                    tok=(char *)calloc(3,sizeof(char));
                    tok=strcpy(tok,"NE");
                    (bl->stream)+=2;
                    printf(" Line no. %d < %s , %s > \n",line_num,"!=",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(3,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"!=");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }
                else
		{
                    	(bl->stream)++;
		     	reportError("!");
			//break;
		}
   	 }
    	 else if((bl->stream)[0]==':')                   
   	 {
                if((bl->stream)[1]=='=')
                {
                    tok=(char *)calloc(9,sizeof(char));
                    tok=strcpy(tok,"ASSIGNOP");
                    (bl->stream)+=2;
                    printf(" Line no. %d < %s , %s > \n",line_num,":=",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(3,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,":=");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }
                else
                {
                    tok=(char *)calloc(6,sizeof(char));
                    tok=strcpy(tok,"COLON");
                    (bl->stream)+=1;
                    printf(" Line no. %d < %s , %s > \n",line_num,":",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,":");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }
    	}
    	else if((bl->stream)[0]=='.')
    	{
                if((bl->stream)[1]=='.')
                {
                    tok=(char *)calloc(8,sizeof(char));
                    tok=strcpy(tok,"RANGEOP");
                    (bl->stream)+=2;
                    printf(" Line no. %d < %s , %s > \n",line_num,"..",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(3,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"..");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
                }
                else
                {
                    	(bl->stream)++;
                    	reportError(".");
                        //break;
                }
    	}
    	else if((bl->stream)[0]==';')
    	{
                tok=(char *)calloc(8,sizeof(char));
                tok=strcpy(tok,"SEMICOL");
                (bl->stream)+=1;
                printf(" Line no. %d < %s , %s > \n",line_num,";",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,";");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
    	}
    	else if((bl->stream)[0]==',')
    	{
		(bl->stream)++;
                tok=(char *)calloc(5,sizeof(char));
                tok=strcpy(tok,"COMMA");
                printf(" Line no. %d < %s , %s > \n",line_num,",",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,",");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
    	}
	else if((bl->stream)[0]=='[')
   	{
                (bl->stream)++;
                tok=(char *)calloc(5,sizeof(char));
                tok=strcpy(tok,"SQBO");
                printf(" Line no. %d < %s , %s > \n",line_num,"[",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"[");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
    	}
   	else if((bl->stream)[0]==']')
    	{
                (bl->stream)++;
                tok=(char *)calloc(5,sizeof(char));
                tok=strcpy(tok,"SQBC");
                printf(" Line no. %d < %s , %s > \n",line_num,"]",tok);
 		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"]");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
    	}
   	else if((bl->stream)[0]=='(')
    	{
                (bl->stream)++;
                tok=(char *)calloc(3,sizeof(char));
                tok=strcpy(tok,"BO");
                printf(" Line no. %d < %s , %s > \n",line_num,"(",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,"(");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
   	}
        else if((bl->stream)[0]==')')
	{
                (bl->stream)++;
                tok=(char *)calloc(3,sizeof(char));
                tok=strcpy(tok,"BC");
                printf(" Line no. %d < %s , %s > \n",line_num,")",tok);
		    lr=(LEXER *)calloc(1,sizeof(LEXER));
		    lr->lex=(char *)calloc(2,sizeof(char));
	     	    lr->lex=strcpy(lr->lex,")");
		    lr->tok=tok;
		    lr->line_no=line_num;
		    return lr;
       }
       else if(isNum((bl->stream)[i]))
       {
	//printf("\n %c\n",(bl->stream)[i]);
        while(1)
        {
            /* lex=(char *)realloc(lex,i+1);
            lex[i]=(bl->stream)[i];
            i++; */

            if(isNum((bl->stream)[i]))
            {
                lex=(char *)realloc(lex,i+1);
                lex[i]=(bl->stream)[i];
                i++; 
            }
            else if((bl->stream)[i]=='.')
            {
                lex=(char *)realloc(lex,i+1);
                lex[i]=(bl->stream)[i];
                i++;
                while(1)
                {
                    if((bl->stream)[i]=='.')
                    {
                       	lex[i-1]='\0';
                        (bl->stream)+=i-1;
                       	tok=(char *)calloc(4,sizeof(char));
			tok=strcpy(tok,"NUM");
			printf(" Line no. %d < %s , %s > \n",line_num,lex,tok);
                   lr=(LEXER *)calloc(1,sizeof(LEXER));
			lr->lex=lex;
			lr->tok=tok;
			lr->line_no=line_num;
			return lr;
		    }
                    if(isNum(bl->stream[i]))
                    {
                        lex=(char *)realloc(lex,i+1);
                        lex[i]=(bl->stream)[i];
                        i++; 
                    }
                    else if((((bl->stream)[i]=='e')||((bl->stream)[i]=='E'))&&isNum(lex[i-1]))
                    {
                            lex=(char *)realloc(lex,i+1);
                            lex[i]=(bl->stream)[i];
                            i++; 
                            if(isNum(bl->stream[i])||((bl->stream)[i]=='+')||((bl->stream)[i]=='-'))
                            {
                                lex=(char *)realloc(lex,i+1);
                                lex[i]=(bl->stream)[i];
                                i++;
                                while(1)
                                {
                                    if(isNum((bl->stream)[i]))
                                    {
                                        lex=(char *)realloc(lex,i+1);
                                        lex[i]=(bl->stream)[i];
                                        i++; 
                                    }
                                    else
                                    {
                                        lex=(char *)realloc(lex,i+1);
                                        lex[i]='\0';                                           
			                (bl->stream)+=i;
                                        tok=(char *)calloc(5,sizeof(char));
                                        tok=strcpy(tok,"RNUM");
                                        printf(" Line no. %d < %s , %s > \n",line_num,lex,tok);
							lr=(LEXER *)calloc(1,sizeof(LEXER));
							lr->lex=lex;
							lr->tok=tok;
							lr->line_no=line_num;
							return lr;
                                    }          
                                }
                            }
                            else
                            {
                            	lex=(char *)realloc(lex,i+1);
                                lex[i]='\0'; 
                                (bl->stream)+=i;   
				i=0;                            
                         	reportError(lex); 
                                break;           
                            }
                    }
                    else if((((bl->stream)[i]=='e')||((bl->stream)[i]=='E'))&&(!isNum(lex[i-1])))
                    {
                    	lex=(char *)realloc(lex,i+2);
                        lex[i]='e';
			lex[i+1]='\0';   
  			(bl->stream)+=i+1;  
			i=0;                           
                 	reportError(lex);
                        break;            
                    }    
                    else
                    {
                        if(isNum((bl->stream)[i-1]))
                        {
                    	        lex=(char *)realloc(lex,i+1);
                        	lex[i]='\0';                        	
                                (bl->stream)+=i;
                        	tok=(char *)calloc(5,sizeof(char));
				tok=strcpy(tok,"RNUM");
                         	printf(" Line no. %d < %s , %s > \n",line_num,lex,tok);
 					lr=(LEXER *)calloc(1,sizeof(LEXER));
					lr->lex=lex;
					lr->tok=tok;
					lr->line_no=line_num;
					return lr;
                        }
			else 
                   	{
                    		lex=(char *)realloc(lex,i+1);
                       		lex[i]='\0';  
				(bl->stream)+=i;  
				i=0;                            
                 		reportError(lex);  
                                break;          
                    	}    

                    }  
                }            
            }
            else
            {
    		lex=(char *)realloc(lex,i+1);
       		lex[i]='\0';                 
		(bl->stream)+=i;
                tok=(char *)calloc(4,sizeof(char));
		tok=strcpy(tok,"NUM");
		printf(" Line no. %d < %s , %s > \n",line_num,lex,tok);
		lr=(LEXER *)calloc(1,sizeof(LEXER));
		lr->lex=lex;
		lr->tok=tok;
		lr->line_no=line_num;
		return lr;
            }   
            if(i==0)
		break;
        }
        }
        else if(isAlphabet(bl->stream[i]))
        {
            //printf("\n loop infinte alpha\n");
	    while(1)
            {   
                if(isAlphabet(bl->stream[i]))
                {
                    lex=(char *)realloc(lex,i+1);
                    lex[i]=(bl->stream)[i];
                    i++; 
                    while(1)
                    {
                        if(isAlphabet((bl->stream)[i])||isNum((bl->stream)[i])||((bl->stream)[i]=='_'))
                        {
                            lex=(char *)realloc(lex,i+1);
                            lex[i]=(bl->stream)[i];
                            i++;
                        }
                        else
                        {
                            lex=(char *)realloc(lex,i+1);
                            lex[i]='\0';
	   			     (bl->stream)+=i;
                            if(search(lex)!=NULL)
                            {
                                printf(" Line no. %d < %s , %s > \n",line_num,lex,search(lex));
					lr=(LEXER *)calloc(1,sizeof(LEXER));
					lr->lex=lex;
					lr->tok=search(lex);
					lr->line_no=line_num;
					return lr;
              		    }
                            else
                            {
                                if(i>20)
                                {
                                	i=0;
                                	reportError(lex);
                                	break;
                          	  }
                                else
                                {
                                	tok=(char *)calloc(3,sizeof(char));
                                	tok=strcpy(tok,"ID");
                                	printf(" Line no. %d < %s , %s > \n",line_num,lex,tok);
						lr=(LEXER *)calloc(1,sizeof(LEXER));
						lr->lex=lex;
						lr->tok=tok;
						lr->line_no=line_num;
						return lr;
                          	  }
                            }
                        }
                                     
                    }  
                    if(i==0)
                    	break;
                }
            }   
        }
        else if((((bl->stream)[0])==32)||(((bl->stream)[0])=='\t'))
        {
		//printf("\n loop infinte space\n");        
		while((((bl->stream)[0])==32)||(((bl->stream)[0])=='\t'))
	                (bl->stream)++;
        }
        else if(((bl->stream)[0])=='\n') 
        {   
		//printf("\n loop infinte next line\n");          
		(bl->stream)++;		
		line_num++;
	}
        else if(((bl->stream)[0])=='\0')
        {    
		//printf("\n loop infinte end\n"); 
		(bl->stream)++;
		return NULL;
		bl=getStream(bl);
        }
        else
 	{
           // printf("\n loop infinte wrong char\n");
            /*if((bl->stream)[0]==EOF)
                 return NULL;*/
	    if(((bl->stream)[0]==1)||((bl->stream)[0]<0)||((bl->stream)[0]<=31))
          {
			(bl->stream)++;              	
			//printf("\n END OF LEXICAL ANALYSIS \n");
			return NULL;
	    }  
	    printf("\n %d\n",(bl->stream)[0]);
    	    lex=(char *)realloc(lex,2);
            lex[0]=(bl->stream)[0];
            lex[1]='\0';
	    (bl->stream)++; 
	    reportError(lex);	    
        }
	free(lex);
	i=0;
	lex=NULL;
    }
}

// **************************************************************************************************

int computeIndex(char *lexeme)
{
    int sum=0;
    for (int i=0;lexeme[i]!='\0';i++)
        sum=sum+lexeme[i];
    return sum%TABLE_SIZE;
}

// **************************************************************************************************

void insert(SYM_ENTRY *entry)
{
    int index=computeIndex(entry->lexeme);
    SYM_ENTRY *temp=NULL;
    if(hashTable[index].len==0)
        hashTable[index].first=entry;
    else
    {
        temp=hashTable[index].first;
        hashTable[index].first=entry;
        entry->next=temp;
    }
    (hashTable[index].len)++;

}

// **************************************************************************************************

char * search(char *lex)
{
    int index=computeIndex(lex);
    //printf("\n %d\n",hashTable[index].len);
    SYM_ENTRY *temp;
    if((hashTable[index].len)==0)
        return NULL;   
    else
    {
        temp=hashTable[index].first;
        for(int i=0;i<hashTable[index].len;i++)
        {
            if(strcmp(temp->lexeme,lex)==0)
                return temp->token;
            temp=temp->next;
        }
        return NULL;
    }
}

// **************************************************************************************************

void symTableDisplay()
{
    int i=0;
    SYM_ENTRY * temp;
    printf("\nHash_Table Entries::\n");
    for(i=0;i<40;i++)
    {
        if(hashTable[i].len!=0)
        {
            temp=hashTable[i].first;
            while(temp!=NULL)
            {
                printf("< %s , %s >\n",temp->lexeme,temp->token);
                temp=temp->next;
            }
        }
    }
}

// **************************************************************************************************

void tokInitializer(LEXER *lr)
{
	/*tok_arr[tok_arr_size].lex=lr->lex;
	tok_arr[tok_arr_size].tok=lr->tok;
	tok_arr[tok_arr_size].line_no=lr->line_no; */
	
	tok_arr[tok_arr_size]=lr;
	tok_arr_size++; 
	tok_arr=(LEXER **)realloc(tok_arr,sizeof(LEXER *)*(tok_arr_size+1));
}

void printTokens()
{
	printf("\n");
	for(int i=0;i<tok_arr_size;i++)
		printf(" Line no. %d < %s , %s > \n",(tok_arr[i])->line_no,(tok_arr[i])->lex,(tok_arr[i])->tok);
}

void lexerCall1(char *argv)
{
	FILE * fp1=fopen(argv,"r");
	FILE * fp2=fopen("cleantext.txt","w");
	BLOCK *b=(BLOCK *)malloc(sizeof(BLOCK));
	LEXER *lr=NULL;
	//removeComments(fp1,fp2);
	fclose(fp2);
	tok_arr_size=0;
	tok_arr=(LEXER **)malloc(sizeof(LEXER *)*(tok_arr_size+1));
	printf("\n");
	b->fp=fp1;
     	b->len=-1;
     	b->stream=NULL;
	b=getStream(b);
	while(!feof(b->fp))
	{
		if(((b->stream)[0]=='\0')||((b->stream)[0]<0))
		{			
			b=getStream(b);
		}	              	
		lr=getNextToken(b);
		while(lr==NULL)
		{
			if(feof(b->fp))
				break;
			if((b->stream)[0]=='\0')
				b=getStream(b);
			lr=getNextToken(b);
		} 
		if(!feof(b->fp))
			tokInitializer(lr);
	}
	fclose(fp1);
}



void lexerCall(char *argv)
{
	FILE * fp1=fopen(argv,"r");
    	//FILE * fp2=fopen("cleantext.txt","w");
	BLOCK *b=(BLOCK *)malloc(sizeof(BLOCK));
	LEXER *lr=NULL;
	//removeComments(fp1,fp2);
	//fclose(fp2);
	//fp2=fopen("cleantext.txt","w");
	b->fp=fp1;
     	b->len=-1;
     	b->stream=NULL;
	printf("\n");
     	 b=getStream(b);
	while(!feof(b->fp))
	{
		if(((b->stream)[0]=='\0')||((b->stream)[0]<0))
		{			
			b=getStream(b);
		}	              	
		lr=getNextToken(b);
		/*if(lr==NULL)
			continue;  */
		while(lr==NULL)
		{
			if(feof(b->fp))
				break;
			if((b->stream)[0]=='\0')
				b=getStream(b);
			lr=getNextToken(b);
		}
	}
	fclose(fp1);
}

void printFile(char *argv,int x)
{
	line_tok=(int *)malloc(sizeof(int)*2);
	line_tok[0]=0;
	line_tok[1]=0;	
	FILE * fp1=fopen(argv,"r");
    	FILE * fp2=fopen("cleantext.txt","w");
	line_count=1;
	char ch;	
	removeComments(fp1,fp2);
	fclose(fp2);
	fp2=fopen("cleantext.txt","r");
	if(x==0)
	{	
		while(!feof(fp2))
		{
			ch=fgetc(fp2);
			if(ch!=EOF)
				printf("%c",ch);
		}
		fclose(fp2);
	}
	
	if(x==1)
	{
		while(!feof(fp2))
		{
			ch=fgetc(fp2);
			if(ch=='\n')
			{
				line_count++;
				line_tok=(int *)realloc(line_tok,sizeof(int)*(line_count+1));
				line_tok[line_count]=0;
			}
			if(ch>32)
				line_tok[line_count]=1;
		}
	}
}	


void showLineTok()
{
	printf("\n\n");
	printf(" no of lines is %d \n",line_count);
	for(int i=1;i<=line_count;i++)
	{
		 if(line_tok[i]==0)
			printf(" LINE NO.%d : No Tokens\n",i);
		 else
			printf(" LINE NO.%d : There are token(s) \n",i); 
	}
}



















