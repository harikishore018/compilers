/*
2017A7PS0133P M VENKAT SAI RAM
2017A7PS0079P ABHISHEK BHARADWAJ
2017A7PS0144P K SAI KISHORE
2017A7PS0141P B HARI KISHORE
2017A7PS0154P G SAI SARATH KRISHNA

GROUP NUMBER 45
*/
#include "parseTree.h"

int node_count=0;
int syn_err;  
NODE *head;
pNode phead;
PARSE_NODE parsetable1[PT_ROWS][PT_COLUMNS];
parseTree PT;


BLOCK *initializer(char *argv)
{
	FILE * fp1=fopen(argv,"r");
	//FILE * fp2=fopen("cleantest.txt","w");
	BLOCK *b=(BLOCK *)malloc(sizeof(BLOCK));
	insertKeywords();
    	//symTableDisplay();	
	//removeComments(fp1,fp2);
	//fclose(fp2);
	//fp2=fopen("cleantest.txt","r");
	b->fp=fp1;
     	b->len=-1;
     	b->stream=NULL;
	printf("\n");
	return b;
}


void printParseTable(int s)
{
	/*char *err="error";
	char *sy="syn";
	char **error=&err;
	char **syn=&sy;	 
*/    	
	int d=0;
	int p=NTCOUNT;
	printf("\n ntcount is %d\n",p);
    for (int i=1;i<NTCOUNT+1;i++)
    {
       for (int j=1;j<s;j++)
       {
           if(strcmp(*(parsetable[i][j].rule),*error)==0)
           {
		//printf("\n1\n");               
		printf("%s         %s\n",*error,parsetable[0][j].symbol);
           }
           else if(strcmp(*(parsetable[i][j].rule),*syn)==0)
           {
		//printf("\n2\n");              
		 printf("%s        %s \n",*syn,parsetable[0][j].symbol);
           }
           else
           {
		//printf("\n3\n");
               while( strcmp((parsetable[i][j].rule)[d],"")!=0)
               {

                   printf("%s  ",(parsetable[i][j].rule)[d]);
                   d++;
                  // printf("\n4\n");
	       }
               d=0;
               printf("            %s\n",parsetable[0][j].symbol);
           }
       }
       printf("\n\n\n");
    }

	for (int j=1;j<s;j++)
	{
		printf("%s \n",parsetable[0][j].symbol);
	}
	printf("\n\n\n");

}

int parseResult(char **stack,int top,int err)
{
	int i=0;
	char hash[]="#";
	if((err==0) && (strcmp(stack[top],"$")!=0))
	{			
		for(i=1;((parsetable[i][0].symbol)!=NULL)&&i<PT_ROWS;i++)
			if(strcmp(parsetable[i][0].symbol,stack[top])==0)
				break;
		for(int j=top;j>0;j--)
		{
			if(isupper(stack[j][0]))
			{
				err++;
				break;
			}
			else
			{
				if(isInFirst(stack[j],hash)==0)
				{
					err++;	
					break;
				}
			}		
		}	
	}
	return err;
}

void parseTreeCall(char *argv,int s)
{
	int err=0;
	//BLOCK *bl=initializer(argv);
	FILE * fp1=fopen(argv,"r");
	//FILE * fp2=fopen("cleantest.txt","w");
	BLOCK *bl=(BLOCK *)malloc(sizeof(BLOCK));
	insertKeywords();
    	//symTableDisplay();	
	//removeComments(fp1,fp2);
	//fclose(fp2);
	//fp2=fopen("cleantest.txt","r");
	bl->fp=fp1;
     	bl->len=-1;
     	bl->stream=NULL;
	printf("\n");
	


	printf("\ns is %d\n",s);
	printf("\n Yahoo\n");
	printFirstAndFollowSets();
	printParseTable(s);
	err=parser(bl);
	syn_err=err;
	if(err!=0)
	{
		//syn_err=err;
		printf("\nThe program is syntactically incorrect. \n");
	}	
	else 
		printf("\n The program is syntactically correct.\n");
	fclose(fp1);

}

int stackBuild(char **rule,int top,char **stack)
{
	int i=0;	
	while(strcmp(rule[i],"")!=0)
		i++;
	//printf(" i is %d \n",i);		
	for(int j=i-1;j>=0;j--)
	{	
		//stack=realloc(stack,top+2);
		//printf("\n push half\n");
		stack[top+1]=rule[j];
		top++;
	}		
	return top;
}

/*int stackBuild(char **rule,int top,char **stack)
{
	if(strcmp(rule[0],"")==0)
		return top;
	printf("\n %s\n",rule[0]);
	top=stackBuild(rule+1,top,stack);
	top=push(top,stack,rule);
	printf("\npush1\n");
	return top;
}*/

int push(int top,char **stack,char **rule)
{
	//printf("\n push \n");
	stack=realloc(stack,top+2);
	//printf("\n push half\n");
	stack[top+1]=rule[0];
	top++;
	return top;
}

void printStack(int top,char **stack)
{
	//printf("Printing Stack :\n");
	//printf("top is %d \n",top);
	//for(int i=top;i>=0;i--)
	//	printf("%s\n",stack[i]); 
}

int pop(int top,char **stack)
{
   // stack=realloc(stack,top-1);
	stack[top]=NULL;    
	top--;
    	return top;
}

int parser(BLOCK *bl)   // # is populated instead of epsilon , the end of each row in grammar table is an empty string  
{
	LEXER *lr=NULL,*temp=NULL,*new=NULL;
	char hash[]="hash";
	int i=0,j=0,err=0;
	printf("\n");
        bl=getStream(bl);
       // char **stack=calloc(2,sizeof(char *));
	char *stack[1000];        
	stack[0]=malloc(sizeof(char)*2);
        stack[0]=strcpy(stack[0],"$");
	stack[1]=production[0][0];
	int top=1;
	head=(NODE *)calloc(1,sizeof(NODE));
	head->tok=production[0][0];
	head->node_num=1;
	head->sibling=NULL;
	head->parent=NULL;
	//head->info_t=NULL;
	node_count=1;
	NODE *cur=head;
	head->c_count=0;
	head->t=1;
	/*for(int z=0;z<tok_arr_size;z++)
	{
		lr=tok_arr[z];
		printf(" Line no. %d < %s , %s > \n",lr->line_no,lr->lex,lr->tok);
		//printf("\n%s %s %d\n",lr->tok,lr->lex,lr->line_no);			
		/*if(lr==NULL)
         		lr=new;
         	else
         	{
         	 	new->next=lr;
         	 	lr=new;
   	 	} */
   	 
	while(!feof(bl->fp))
	{
		if(((bl->stream)[0]=='\0')||((bl->stream)[0]<0))			
			bl=getStream(bl);	            	
		new=getNextToken(bl);
		if(new==NULL)
			continue;
		printf("\n%s %s %d\n",new->tok,new->lex,new->line_no);	
		if(lr==NULL)
         		lr=new;
         	else
         	{
         	 	new->next=lr;
         	 	lr=new;
   	 	}
   	 	
   		
   	 	while(1)
   	 	{
   	 	
   	 		if(strcmp(stack[top],lr->tok)==0) //
   	 		{
				//printf("\n  %s  \n",lr->tok);
				top=pop(top,stack);
				printStack(top,stack);
					
				if(err==0)
					cur=buildParseTree(NULL,cur,lr);
				if(strcmp(stack[top],"$")==0)
				{
					printf("\n err is  %d ",err);				
					return parseResult(stack,top,err);
				}				
				break;
   	 		}
 			//printf("\n  2 \n");
   	 		for(int x=1;((parsetable[0][x].symbol)!=NULL)&&i<PT_COLUMNS;x++)
   	 	  		if(strcmp(parsetable[0][x].symbol,lr->tok)==0)
 	  			{
					j=x;
 	  				break;
  				}
	 		//	printf("\n 3 \n");
  			for(int y=1;((parsetable[y][0].symbol)!=NULL)&&i<PT_ROWS;y++)
  				if(strcmp(parsetable[y][0].symbol,stack[top])==0)
  			 	{
  			 		i=y;
		 			break;
	 			}
				//printf("\n  i=%d j=%d \n",i,j);
				//printf("\n parse table symbol is %s   %s \n",parsetable[0][j].symbol,parsetable[i][0].symbol);

   	 	  		//............................................................
   	 	  		
				if(strcmp(*(parsetable[i][j].rule),*error)==0)
				{
		 			printf("\n  5  \n");
					err++;
					printf("\n In Line no. %d \"Syntactial Error\": Wrong token %s \n",lr->line_no,lr->lex);
					break;	
				}
				else if(strcmp(*(parsetable[i][j].rule),*syn)==0)
		   	 	{
 		 			printf("\n  6  \n");
			   	 	err++;
			   	 	printf("\n In Line no. %d \"Syntactial Error\": Missing token(s) \n",lr->line_no);
			   	 	pop(top,stack);
			   	 	if(strcmp(stack[top],"$")==0)
					{
						printf("\n err is  %d ",err);
   	 		     			return parseResult(stack,top,err);
					}	 	
		   	 	}
		   	 	else
		   	 	{
		 			//printf("\n  %d %d \n",i,j);
					//printf("top is %d\n",top);	   	 	     		
					top=pop(top,stack);
					//printf("top is %d\n",top);
					//printf("\n %s   before if \n",*((parsetable[i][j].rule)));
		 	     		if(strcmp(*((parsetable[i][j].rule)+2),"#")!=0)
		 	     		{
						//printf("\n watt the shuck\n");                 				
						//printf("\n %s \n",*((parsetable[i][j].rule)+2));
						printf("cur head is %s\n ",cur->tok);                 				
						top=stackBuild((parsetable[i][j].rule)+2,top,stack);
						//printf("top is %d\n",top);           				
					}
					//printf("\n 9\n");
					printStack(top,stack);
           				//printf("\n 9\n");
                 			
					if(err==0)
                 				cur=buildParseTree((parsetable[i][j].rule)+2,cur,lr);

           				//printf("\n 10 \n");
           				if((cur==NULL)||(strcmp(stack[top],"$")==0))
					{
						printf("\n err is  %d ",err);
						return parseResult(stack,top,err);
					}
					/*this means if we parse Tree has reached the bottom then we should return correct syntactically iff token stream is empty */
     					//printf("\n 11 \n");
	                  }	
	                  
      		}                   			                       
	}
	printf("\n err is  %d ",err);
	return parseResult(stack,top,err);
}


NODE *buildParseTree(char **rule,NODE *cur,LEXER *lr)
{
	int i=0;
	NODE *new;
	cur->c_count=0;
	NODE *temp=NULL;
	NODE *temp_node=NULL;


	//printf("\n 222 \n");		
	//printf("\nCurrent token is %s \n the token required is %s \n ",cur->tok,lr->tok);	
	if(strcmp(cur->tok,lr->tok)==0)
	{
		cur->lex=lr->lex;
		cur->line_no=lr->line_no;
		cur->t=0;
		//cur->info_t=lr;
	}	
	//printf("\n 111 \n");
	/*if(rule==NULL)
		printf("Rule is NULL\n");		
	else
		printf("\n rule is %s \n",rule[0]); */
	if(rule!=NULL)
	{
		//printf("\n enter \n");		
		while((strcmp(rule[i],"")!=0)&&((cur->lex)==NULL))
		{
			//printf("done bro\n");			
			new=(NODE *)calloc(1,sizeof(NODE));
			(cur->node)[i]=new;
			new->parent=cur;
			new->tok=rule[i];
			cur->t=1;
			//new->info_t=NULL;
			(cur->c_count)++;
			node_count++;
	      	new->node_num=node_count;
	      	if(i!=0)
	      		((cur->node)[i-1])->sibling=new;
			new->lex=NULL;
			new->line_no=0;
			for(int j=0;j<GRAMMAR_LEN;j++)
		  		(new->node)[j]=NULL;
			i++;                                                   // sibling and cur_node;
		}
	}
	//printf("\n enter \n");	
	//printf("\ncur -> lex is %s \n",cur->lex);			
	if((rule!=NULL)&&((cur->lex)==NULL))
	{

		printf("\ni is %d \n",i);
		//temp_node=(cur->node	      	
		(cur->node)[i-1]->sibling=NULL;  
		//printf("1\n");
	}	
	if((rule==NULL)||(strcmp(rule[0],"#")==0))
		temp=cur;
	else
	{
		cur=(cur->node)[0];
	//	printf(" \ncurrent token is %s\n\n............................................................\n\n",cur->tok);
		return cur;
	}		
	while(temp!=NULL)
	{
		if((temp->sibling)!=NULL)
		{
			cur=temp->sibling;
			//printf(" \ncurrent token is %s\n\n............................................................\n\n",cur->tok);
			return cur;
		}
		temp=temp->parent;
	}
	if(temp==NULL)
		return temp;
}

/* void printParseTree(NODE *head)
{
	int num=head->c_count;
	if(head->node[0]==NULL)
	{
		printDetails(head);
		return;
	}
	for(int i=0;i<(num-1);i++)
		printParseTree((head->node)[i]);

	printDetails(head);

	printParseTree(head->node[num-1]);
}*/

void printParseTree(NODE *head)
{
	int num=head->c_count;
	if(head->node[0]==NULL)
	{
		printDetails(head);
		return;
	}
	printParseTree((head->node)[0]);

	printDetails(head);

	for(int i=1;i<=(num-1);i++)
		printParseTree(head->node[i]);
}



void printDetails(NODE *head)
{
	/*if((head->lex)!=NULL)
	{
		
		printf(" < LEXEME , LINE NO. , TOKEN , PARENT , IS_LEAF_NODE > ::  < %s , %d , %s , %s , YES >\n",head->lex,head->line_no,head->tok,(head->parent)->tok);
	}	
	else if(strcmp((head->tok),"#")==0)
	{	
		printf(" <  CURRENT_NODE , PARENT , IS_LEAF_NODE > ::  < %s , %s , YES >\n",head->tok,(head->parent)->tok);
	}	
	else
	{
		if((head->parent)==NULL)
			printf(" < CURRENT_NODE , PARENT , IS_LEAF_NODE > ::  < %s , %s , NO >\n",head->tok,"ROOT");
		else
			printf(" < CURRENT NODE , PARENT , IS_LEAF_NODE > ::  < %s , %s , NO >\n",head->tok,(head->parent)->tok);
	}*/
	printf(" TOKEN :      %s %d\n",head->tok,head->t);
}
		
void printASTParseTree(pNode phead)
{
	//printf(" \n%s  %s\n",phead->tok,((phead->node)[0])->tok);
	int num=phead->no_of_child;
	if(phead->node[0]==NULL)
	{
		printASTDetails(phead);
		return;
	}
	printASTParseTree((phead->node)[0]);

	printASTDetails(phead);

	for(int i=1;i<=(num-1);i++)
		printASTParseTree((phead->node)[i]);

}
	
	
void printASTDetails(pNode phead)
{
	//printf("yessssssssssss");	
	printf(" TOKEN :      %s \n",phead->tok);
}

void createNewParseTree()
{
	phead=(pNode)malloc(sizeof(struct pNode));
	phead->t=head->t;	
	(phead->e).nt=calculateNT(head->tok);
	phead->tok=head->tok;
	phead->no_of_child=head->c_count;
	phead->token_link=NULL;	
	phead->next=NULL;
	phead->parent=NULL;
	for(int i=0;i<GRAMMAR_LEN;i++)
		(phead->node)[i]=NULL;
	(phead->child).size=head->c_count;
	createASTParseTree(phead,head);  
	PT.root=phead;
	PT.c_node=NULL;
	PT.height=0; 
	
}

int calculateNT(char *tok)
{
	int i;
	for (i=1;i<NTCOUNT+1;i++)
	{
		if(strcmp(tok,parsetable[i][0].symbol)==0)
			return i-1;
	}
}	


int calculateT(char *tok)
{
	int j;
	for (j=1;j<t_count;j++)
	{
		if(strcmp(tok,parsetable[0][j].symbol)==0)
			return j-1;
	}
	return j-1;
}	

void createASTParseTree(pNode phead,NODE *head)
{     
	pNode new,prev;
	NODE *temp;
	if(head->c_count==0)
	{
		(phead->child).front=NULL;
		(phead->child).back=NULL;
		(phead->child).size=0;
		return;
	}
    
	for(int i=0;i<=(phead->no_of_child-1);i++)
	{
		new=(pNode)malloc(sizeof(struct pNode));
		temp=(head->node)[i];		

		new->t=temp->t;

		if((temp->t)==0)
		{
			(new->e).t=calculateT(temp->tok);
		}
		else
		{
			(new->e).nt=calculateNT(temp->tok);
		}

		new->tok=temp->tok;

		new->no_of_child=temp->c_count;

		if(isupper((temp->tok)[0]))     //   (temp->t)==0
		{
			new->token_link=(tokenInfo *)calloc(sizeof(struct tokenInfo),1);
			(new->token_link)->lex=temp->lex;
			(new->token_link)->s=calculateT(temp->tok);  
			(new->token_link)->lno=temp->line_no; 
		}		

		new->next=NULL;
		if(i!=0)
			prev->next=new;
		
		new->parent=phead; 

		(phead->node)[i]=new;
		for(int x=0;x<GRAMMAR_LEN;x++)
			(new->node)[x]=NULL;

		(new->child).size=temp->c_count;
		if(i==0)
			(phead->child).front=new;
		else if(i==(phead->no_of_child-1))
			(phead->child).back=new;   	
		createASTParseTree(new,temp);
		prev=new;
	}
}













