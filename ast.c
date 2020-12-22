/*
2017A7PS0133P M VENKAT SAI RAM
2017A7PS0079P ABHISHEK BHARADWAJ
2017A7PS0144P K SAI KISHORE
2017A7PS0141P B HARI KISHORE
2017A7PS0154P G SAI SARATH KRISHNA

GROUP NUMBER 45
*/

#include "ast.h"
int ast_node_count;
char ***ast_rules;
AST_NODE *ast_head;

void astCreateCall(NODE *head)
{
	int num=head->c_count;
	if(head->node[0]==NULL)
	{
		printASTTreeDetails(head);
		return;
	}
	//printParseTree((head->node)[0]);
	printASTTreeDetails(head);

	for(int i=0;i<=(num-1);i++)
		astCreateCall(head->node[i]);
}

int isRequired (char *tok)
{
	if((strcmp(tok,"DECLARE")==0) || (strcmp(tok,"SEMICOL")==0) || (strcmp(tok,"DRIVERDEF")==0) || (strcmp(tok,"DRIVER")==0) || (strcmp(tok,"PROGRAM")==0) || (strcmp(tok,"DRIVERENDDEF")==0) || (strcmp(tok,"DEF")==0) || (strcmp(tok,"ENDDEF")==0) || (strcmp(tok,"TAKES")==0) || (strcmp(tok,"INPUT")==0) || (strcmp(tok,"SQBO")==0) || (strcmp(tok,"SQBC")==0) || (strcmp(tok,"RETURNS")==0) || (strcmp(tok,"COMMA")==0) || (strcmp(tok,"OF")==0) || (strcmp(tok,"GET_VALUE")==0) || (strcmp(tok,"BO")==0) || (strcmp(tok,"BC")==0) || (strcmp(tok,"PRINT")==0) || (strcmp(tok,"ASSIGNOP")==0) || (strcmp(tok,"USE")==0) || (strcmp(tok,"WITH")==0) || (strcmp(tok,"PARAMETERS")==0) || (strcmp(tok,"CASE")==0) || (strcmp(tok,"BREAK")==0) || (strcmp(tok,"DEFAULT")==0) || (strcmp(tok,"IN")==0) )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void printASTTreeDetails(NODE *head)
{
/*	if(isRequired(head->tok))
	{
		if((head->lex)!=NULL)
		{		
			printf("  <TOKEN , %s> < LEXEME %s> < LINE NO., %d> \n",head->tok,head->lex,head->line_no);
		}	
		else if(strcmp((head->tok),"#")==0)
		{	
			//printf(" <  < %s , %s , YES >\n",head->tok,(head->parent)->tok);
		}	
		else
		{
			if((head->node[0])!=NULL)
			{		
				if(strcmp(((head->node[0])->tok),"#")==0)
					printf(" Non_Terminal %s -> #(empty rule)\n",head->tok);
				else
					printf(" Non_Terminal %s ->\n",head->tok);	
			}		
		} 
		//printf(" :      %s %d\n",head->tok,head->t);
	}
*/	
	if(isRequired(head->tok))
	{
		ast_node_count++;
		if((head->lex)!=NULL)
		{		
			printf("  %s < Lexeme , Line no. > : < %s , %d >  \n",head->tok,head->lex,head->line_no);
		}	
		else if(strcmp((head->tok),"#")==0)
		{	
			printf(" #(%s)\n",(head->parent)->tok);
		}	
		else
		{
			printf(" < %s >\n",head->tok);
		}
          
		//printf(" :      %s %d\n",head->tok,head->t);
	}



}
	


void ast_constrcution()
{
	ast_head=(AST_NODE *)calloc(1,sizeof(AST_NODE));
	ast_head->parent=NULL;
	ast_head->left=NULL;
	ast_head->right=NULL;
	ast_head->value=NULL;
	ast_head->tok=head->tok;	
	NODE *temp=head;
	AST_NODE *cur=ast_head;
	while(1)
	{
		if((temp->node)[0]!=NULL) 
		{
			if(strcmp(temp->tok,"grammar")==0)
			{
				populateAst(0,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"moduleDeclarations")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"moduleDeclaration")==0)
				{
					populateAst(1,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(2,cur,temp);
					//add_values(cur,((temp->node)[0])->tok);			
				}
			}
			else if(strcmp(temp->tok,"driverModule")==0)
			{
				populateAst(3,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"moduleDef")==0)
			{
				populateAst(4,cur,temp);
				//symbolTable
			}
			else if(strcmp(temp->tok,"otherMOdules")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(6,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(5,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"module")==0)
			{
				populateAst(7,cur,temp);
				//add_values(
			}
			else if(strcmp(temp->tok,"ret")==0) //handle carefully
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(9,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(8,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"input_plist")==0)
			{
				populateAst(10,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"n1")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(12,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(11,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"dataType")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"INTEGER")==0)
				{
					populateAst(13,cur,temp);
					//add_values();
				}
				else if(strcmp(((temp->node)[0])->tok,"REAL")==0)
				{
					populateAst(14,cur,temp);
					//add_values();
				}
				if(strcmp(((temp->node)[0])->tok,"BOOLEAN")==0)
				{
					populateAst(15,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(16,cur,temp);
					//add_values();
				}				
			}
			else if(strcmp(temp->tok,"statements")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(17,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(22,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"type")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"INTEGER")==0)
				{
					populateAst(18,cur,temp);
					//add_values();
				}
				else if(strcmp(((temp->node)[0])->tok,"REAL")==0)
				{
					populateAst(19,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(20,cur,temp);
					//add_values();
				}
			}
			else if(strcmp(temp->tok,"statement")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"ioStmt")==0)
				{
					populateAst(25,cur,temp);
					//add_values();
				}
				else if(strcmp(((temp->node)[0])->tok,"conditionalStmt")==0)
				{
					populateAst(26,cur,temp);
					//add_values();
				}
				else if(strcmp(((temp->node)[0])->tok,"declareStmt")==0)
				{
					populateAst(27,cur,temp);
					//add_values();
				}
				else if(strcmp(((temp->node)[0])->tok,"iterativeStmt")==0)
				{
					populateAst(28,cur,temp);
					//add_values();
				}
				else
				{
					temp=((temp->node)[0]);
					if(strcmp(((temp->node)[0])->tok,"assignmentStmt")==0)
					{
						populateAst(23,cur,temp);
						//add_values();
					}
					else 
					{
						populateAst(24,cur,temp);
						//add_values();
					}
					temp=temp->parent;
				}
			}
			else if(strcmp(temp->tok,"ioStmt")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"GET_VALUE")==0)
				{
					populateAst(29,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(21,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"var")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"boolConstt")==0)
				{
					populateAst(30,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(31,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"boolConstt")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"TRUE")==0)
				{
					populateAst(32,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(33,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"var_id_num")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"NUM")==0)
				{
					populateAst(34,cur,temp);
					//add_values();
				}
				else if(strcmp(((temp->node)[0])->tok,"RNUM")==0)
				{
					populateAst(35,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(36,cur,temp);
					cur=cur->child;
					populateAst(37,cur,temp);
					//add_values();
				}
			}
			else if(strcmp(temp->tok,"whichId")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(39,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(38,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"assignmentStmt")==0) //handleCarefully
			{
				populateAst(40,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"index")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"NUM")==0)
				{
					populateAst(41,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(42,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"moduleReuseStmt")==0)
			{
				populateAst(43,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"optional")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(45,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(44,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"idList")==0)
			{
				populateAst(46,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"n3")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(48,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(47,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"declareStmt")==0)
			{
				populateAst(49,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"conditionalStmt")==0)
			{
				populateAst(50,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"caseStmts")==0)
			{
				populateAst(51,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"n9")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(53,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(52,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"value")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"NUM")==0)
				{
					populateAst(54,cur,temp);
					//add_values();
				}
				else if(strcmp(((temp->node)[0])->tok,"TRUE")==0)
				{
					populateAst(55,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(56,cur,temp);
					//add_values();
				}
			}
			else if(strcmp(temp->tok,"default")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(58,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(57,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"iterativeStmt")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"WHILE")==0)
				{
					populateAst(60,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(59,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"expression")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"u")==0)
				{
					populateAst(62,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(61,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"u")==0)
			{
				populateAst(63,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"new_NT")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"var_id_num")==0)
				{
					populateAst(64,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(65,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"unary_op")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"PLUS")==0)
				{
					populateAst(66,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(67,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"arithmeticOrBooleanExpr")==0)
			{
				populateAst(68,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"n7")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(70,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(69,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"anyTerm")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"boolConstt")==0)
				{
					populateAst(72,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(71,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"n8")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(75,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(73,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"arithmeticExpr")==0)
			{
				populateAst(76,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"n4")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(78,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(77,cur,temp);
					//add_values();				
				}
			}
			else if(strcmp(temp->tok,"term")==0)
			{
				populateAst(79,cur,temp);
				//add_values();
			}
			else if(strcmp(temp->tok,"n5")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"#")==0)
				{
					populateAst(81,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(80,cur,temp);
					//add_values();				
				}
			}			
			else if(strcmp(temp->tok,"factor")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"BO")==0)
				{
					populateAst(82,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(83,cur,temp);
					//add_values();				
				}
			}			
			else if(strcmp(temp->tok,"op1")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"PLUS")==0)
				{
					populateAst(84,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(85,cur,temp);
					//add_values();				
				}
			}			
			else if(strcmp(temp->tok,"op2")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"MUL")==0)
				{
					populateAst(86,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(87,cur,temp);
					//add_values();				
				}
			}			
			else if(strcmp(temp->tok,"logicalOp")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"AND")==0)
				{
					populateAst(88,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(89,cur,temp);
					//add_values();				
				}
			}	
			else if(strcmp(temp->tok,"relationalOP")==0)
			{
				if(strcmp(((temp->node)[0])->tok,"LE")==0)
				{
					populateAst(90,cur,temp);
					//add_values();
				}
				else if(strcmp(((temp->node)[0])->tok,"GE")==0)
				{
					populateAst(91,cur,temp);
					//add_values();
				}
				else if(strcmp(((temp->node)[0])->tok,"LT")==0) 
				{
					populateAst(92,cur,temp);
					//add_values();
				}
				else if(strcmp(((temp->node)[0])->tok,"GT")==0)
				{
					populateAst(93,cur,temp);
					//add_values();
				}
				else if(strcmp(((temp->node)[0])->tok,"EQ")==0)
				{
					populateAst(94,cur,temp);
					//add_values();
				}
				else
				{
					populateAst(74,cur,temp);
					//add_values();
				}
				
			}
		}

	}

}

void populateAst(int index,AST_NODE *cur,NODE *present)
{
	int i=2;
	NODE *temp=present;
	AST_NODE *new,*prev;
	prev=NULL;
	new=NULL;
	while(strcmp(ast_rules[index][i],"")!=0)
	{
		new=createNew();
		new->tok=ast_rules[index][i];
		new->parent=cur;
		if(i==2)
			cur->child=new;		
		else
			prev->right=new;	
		new->left=prev;
		prev=new;
	}
	
}


AST_NODE *createNew()
{
	AST_NODE *new=(AST_NODE *)malloc(sizeof(AST_NODE));
	return new;
}

void createAstRules()
{

	for(int x=0;x<RULECOUNT;x++)
	{
		ast_rules[x] = (char**) malloc(sizeof(char*) * COLUMNS);
		for(int y=0;y<COLUMNS;y++)
			ast_rules[x][y] = (char*) malloc(sizeof(char) * 25);
        }
	
	ast_rules[0][0]=strcpy(ast_rules[0][0],"grammar");
	ast_rules[0][1]=strcpy(ast_rules[0][1],"->");
	ast_rules[0][2]=strcpy(ast_rules[0][2],"moduleDeclarations");
	ast_rules[0][3]=strcpy(ast_rules[0][3],"otherModules");
	ast_rules[0][4]=strcpy(ast_rules[0][4],"driverDefintion");
	ast_rules[0][5]=strcpy(ast_rules[0][5],"otherModules");
	strcpy(ast_rules[0][6],"");

	ast_rules[1][0]=strcpy(ast_rules[1][0],"moduleDeclarations");
	ast_rules[1][1]=strcpy(ast_rules[1][1],"->");
	ast_rules[1][2]=strcpy(ast_rules[1][2],"MODULE");
	ast_rules[1][3]=strcpy(ast_rules[1][3],"ID");
	ast_rules[1][4]=strcpy(ast_rules[1][4],"moduleDeclarations");
	ast_rules[1][5]=strcpy(ast_rules[1][5],"");


	ast_rules[2][0]=strcpy(ast_rules[2][0],"moduleDeclarations");
	ast_rules[2][1]=strcpy(ast_rules[2][1],"->");
	ast_rules[2][2]=strcpy(ast_rules[2][2],"#");
	strcpy(ast_rules[2][3],"");

	ast_rules[3][0]=strcpy(ast_rules[3][0],"driverModule");
	ast_rules[3][1]=strcpy(ast_rules[3][1],"->");
	ast_rules[3][2]=strcpy(ast_rules[3][2],"start");
	ast_rules[3][3]=strcpy(ast_rules[3][3],"statements");
	ast_rules[3][4]=strcpy(ast_rules[3][4],"end");
	ast_rules[3][4]=strcpy(ast_rules[3][4],"");
	
	ast_rules[4][0]=strcpy(ast_rules[4][0],"module_Def");
	ast_rules[4][1]=strcpy(ast_rules[4][1],"->");
	ast_rules[4][2]=strcpy(ast_rules[4][2],"start");
	ast_rules[4][3]=strcpy(ast_rules[4][3],"statements");
	ast_rules[4][4]=strcpy(ast_rules[4][4],"end");
	strcpy(ast_rules[4][7],"");

	ast_rules[5][0]=strcpy(ast_rules[5][0],"otherModules");
	ast_rules[5][1]=strcpy(ast_rules[5][1],"->");
	ast_rules[5][2]=strcpy(ast_rules[5][2],"module");
	ast_rules[5][3]=strcpy(ast_rules[5][3],"otherModules");
	strcpy(ast_rules[5][4],"");

	ast_rules[6][0]=strcpy(ast_rules[6][0],"otherModules");
	ast_rules[6][1]=strcpy(ast_rules[6][1],"->");
	ast_rules[6][2]=strcpy(ast_rules[6][2],"#");
	strcpy(ast_rules[6][3],"");

	
	ast_rules[7][0]=strcpy(ast_rules[7][0],"module");
	ast_rules[7][1]=strcpy(ast_rules[7][1],"->");
	ast_rules[7][2]=strcpy(ast_rules[7][2],"ID");
	ast_rules[7][3]=strcpy(ast_rules[7][3],"input_plist");
	ast_rules[7][4]=strcpy(ast_rules[7][4],"ret");
	strcpy(ast_rules[7][5],"");

	ast_rules[8][0]=strcpy(ast_rules[8][0],"ret");
	ast_rules[8][1]=strcpy(ast_rules[8][1],"->");
	ast_rules[8][2]=strcpy(ast_rules[8][2],"ID");
	ast_rules[8][3]=strcpy(ast_rules[8][3],"type");
	ast_rules[8][4]=strcpy(ast_rules[8][4],"ret");
	strcpy(ast_rules[8][7],"");

	ast_rules[9][0]=strcpy(ast_rules[9][0],"ret");
	ast_rules[9][1]=strcpy(ast_rules[9][1],"->");
	ast_rules[9][2]=strcpy(ast_rules[9][2],"#");
	strcpy(ast_rules[9][3],"");

	ast_rules[10][0]=strcpy(ast_rules[10][0],"input_plist");
	ast_rules[10][1]=strcpy(ast_rules[10][1],"->");
	ast_rules[10][2]=strcpy(ast_rules[10][2],"ID");
	ast_rules[10][4]=strcpy(ast_rules[10][4],"dataType");
	ast_rules[10][5]=strcpy(ast_rules[10][5],"n1");
	strcpy(ast_rules[10][6],"");

	ast_rules[11][0]=strcpy(ast_rules[11][0],"n1");
	ast_rules[11][1]=strcpy(ast_rules[11][1],"->");
	ast_rules[11][3]=strcpy(ast_rules[11][3],"ID");
	ast_rules[11][5]=strcpy(ast_rules[11][5],"dataType");
	ast_rules[11][6]=strcpy(ast_rules[11][6],"n1");
	strcpy(ast_rules[11][7],"");

	ast_rules[12][0]=strcpy(ast_rules[12][0],"n1");
	ast_rules[12][1]=strcpy(ast_rules[12][1],"->");
	ast_rules[12][2]=strcpy(ast_rules[12][2],"#");
	strcpy(ast_rules[12][3],"");

	ast_rules[13][0]=strcpy(ast_rules[13][0],"dataType");
	ast_rules[13][1]=strcpy(ast_rules[13][1],"->");
	ast_rules[13][2]=strcpy(ast_rules[13][2],"INTEGER");
	strcpy(ast_rules[13][3],"");
	
	ast_rules[14][0]=strcpy(ast_rules[14][0],"dataType");
	ast_rules[14][1]=strcpy(ast_rules[14][1],"->");
	ast_rules[14][2]=strcpy(ast_rules[14][2],"REAL");
	strcpy(ast_rules[14][3],"");
	
	ast_rules[15][0]=strcpy(ast_rules[15][0],"dataType");
	ast_rules[15][1]=strcpy(ast_rules[15][1],"->");
	ast_rules[15][2]=strcpy(ast_rules[15][2],"BOOLEAN");
	strcpy(ast_rules[15][3],"");

	ast_rules[16][0]=strcpy(ast_rules[16][0],"dataType");
	ast_rules[16][1]=strcpy(ast_rules[16][1],"->");
	ast_rules[16][2]=strcpy(ast_rules[16][2],"ARRAY");
	ast_rules[16][3]=strcpy(ast_rules[16][3],"index");
	ast_rules[16][4]=strcpy(ast_rules[16][4],"index");
	ast_rules[16][5]=strcpy(ast_rules[16][5],"type");
	ast_rules[16][6]=strcpy(ast_rules[16][6],"");

	ast_rules[17][0]=strcpy(ast_rules[17][0],"statements");
	ast_rules[17][1]=strcpy(ast_rules[17][1],"->");
	ast_rules[17][2]=strcpy(ast_rules[17][2],"#");
	strcpy(ast_rules[17][3],"");

	ast_rules[18][0]=strcpy(ast_rules[18][0],"type");
	ast_rules[18][1]=strcpy(ast_rules[18][1],"->");
	ast_rules[18][2]=strcpy(ast_rules[18][2],"INTEGER");
	strcpy(ast_rules[18][3],"");
	
	ast_rules[19][0]=strcpy(ast_rules[19][0],"type");
	ast_rules[19][1]=strcpy(ast_rules[19][1],"->");
	ast_rules[19][2]=strcpy(ast_rules[19][2],"REAL");
	strcpy(ast_rules[19][3],"");
	
	ast_rules[20][0]=strcpy(ast_rules[20][0],"type");
	ast_rules[20][1]=strcpy(ast_rules[20][1],"->");
	ast_rules[20][2]=strcpy(ast_rules[20][2],"BOOLEAN");
	strcpy(ast_rules[20][3],"");

	ast_rules[21][0]=strcpy(ast_rules[21][0],"ioStmt");
	ast_rules[21][1]=strcpy(ast_rules[21][1],"->");
	ast_rules[21][2]=strcpy(ast_rules[21][2],"var");
	ast_rules[21][3]=strcpy(ast_rules[21][3],"");
	
    	ast_rules[22][0]=strcpy(ast_rules[22][0],"statements");
	ast_rules[22][1]=strcpy(ast_rules[22][1],"->");
	ast_rules[22][2]=strcpy(ast_rules[22][2],"statement");
	ast_rules[22][3]=strcpy(ast_rules[22][3],"statements");
	strcpy(ast_rules[22][4],"");

	
	ast_rules[23][0]=strcpy(ast_rules[23][0],"statement");
	ast_rules[23][1]=strcpy(ast_rules[23][1],"->");
	ast_rules[23][2]=strcpy(ast_rules[23][2],"assignmentStmt");
	strcpy(ast_rules[23][3],"");

	ast_rules[24][0]=strcpy(ast_rules[24][0],"statement");
	ast_rules[24][1]=strcpy(ast_rules[24][1],"->");
	ast_rules[24][2]=strcpy(ast_rules[24][2],"moduleReuseStmt");
	strcpy(ast_rules[24][3],"");
	
	ast_rules[25][0]=strcpy(ast_rules[25][0],"statement");
	ast_rules[25][1]=strcpy(ast_rules[25][1],"->");
	ast_rules[25][2]=strcpy(ast_rules[25][2],"ioStmt");
	strcpy(ast_rules[25][3],"");


	ast_rules[26][0]=strcpy(ast_rules[26][0],"statement");
	ast_rules[26][1]=strcpy(ast_rules[26][1],"->");
	ast_rules[26][2]=strcpy(ast_rules[26][2],"conditionalStmt");
	strcpy(ast_rules[26][3],"");

	ast_rules[27][0]=strcpy(ast_rules[27][0],"statement");
	ast_rules[27][1]=strcpy(ast_rules[27][1],"->");
	ast_rules[27][2]=strcpy(ast_rules[27][2],"declareStmt");
	strcpy(ast_rules[27][3],"");
	

	ast_rules[28][0]=strcpy(ast_rules[28][0],"statement");
	ast_rules[28][1]=strcpy(ast_rules[28][1],"->");
	ast_rules[28][2]=strcpy(ast_rules[28][2],"iterativeStmt");
	strcpy(ast_rules[28][3],"");

	ast_rules[29][0]=strcpy(ast_rules[29][0],"ioStmt");
	ast_rules[29][1]=strcpy(ast_rules[29][1],"->");
	ast_rules[29][2]=strcpy(ast_rules[29][2],"GET_VALUE");
	ast_rules[29][3]=strcpy(ast_rules[29][3],"ID");
	ast_rules[29][4]=strcpy(ast_rules[29][4],"");

	ast_rules[30][0]=strcpy(ast_rules[30][0],"var");
	ast_rules[30][1]=strcpy(ast_rules[30][1],"->");
	ast_rules[30][2]=strcpy(ast_rules[30][2],"boolConstt");
	strcpy(ast_rules[30][3],"");

	ast_rules[31][0]=strcpy(ast_rules[31][0],"var");
	ast_rules[31][1]=strcpy(ast_rules[31][1],"->");
	ast_rules[31][2]=strcpy(ast_rules[31][2],"var_id_num");
	strcpy(ast_rules[31][3],"");

	ast_rules[32][0]=strcpy(ast_rules[32][0],"boolConstt");
	ast_rules[32][1]=strcpy(ast_rules[32][1],"->");
	ast_rules[32][2]=strcpy(ast_rules[32][2],"TRUE");
	strcpy(ast_rules[32][3],"");

	ast_rules[33][0]=strcpy(ast_rules[33][0],"boolConstt");
	ast_rules[33][1]=strcpy(ast_rules[33][1],"->");
	ast_rules[33][2]=strcpy(ast_rules[33][2],"FALSE");
	strcpy(ast_rules[33][3],"");

	ast_rules[34][0]=strcpy(ast_rules[34][0],"var_id_num");
	ast_rules[34][1]=strcpy(ast_rules[34][1],"->");
	ast_rules[34][2]=strcpy(ast_rules[34][2],"NUM");
	strcpy(ast_rules[34][3],"");

	ast_rules[35][0]=strcpy(ast_rules[35][0],"var_id_num");
	ast_rules[35][1]=strcpy(ast_rules[35][1],"->");
	ast_rules[35][2]=strcpy(ast_rules[35][2],"RNUM");
	strcpy(ast_rules[35][3],"");

	ast_rules[36][0]=strcpy(ast_rules[36][0],"var_id_num");
	ast_rules[36][1]=strcpy(ast_rules[36][1],"->");
	ast_rules[36][2]=strcpy(ast_rules[36][2],"var_name");
	strcpy(ast_rules[36][3],"");

	ast_rules[37][0]=strcpy(ast_rules[37][0],"var_name");
	ast_rules[37][1]=strcpy(ast_rules[37][1],"->");
	ast_rules[37][2]=strcpy(ast_rules[37][2],"ID");
	ast_rules[37][3]=strcpy(ast_rules[37][3],"whichId");
	strcpy(ast_rules[37][4],"");

	ast_rules[38][0]=strcpy(ast_rules[38][0],"whichId");
	ast_rules[38][1]=strcpy(ast_rules[38][1],"->");
	ast_rules[38][2]=strcpy(ast_rules[38][2],"index");
	ast_rules[38][3]=strcpy(ast_rules[38][3],"");

	ast_rules[39][0]=strcpy(ast_rules[39][0],"whichId");
	ast_rules[39][1]=strcpy(ast_rules[39][1],"->");
	ast_rules[39][2]=strcpy(ast_rules[39][2],"#");
	strcpy(ast_rules[39][3],"");

	ast_rules[40][0]=strcpy(ast_rules[40][0],"assignmentStmt");
	ast_rules[40][1]=strcpy(ast_rules[40][1],"->");
	ast_rules[40][2]=strcpy(ast_rules[40][2],"var_name");
	ast_rules[40][3]=strcpy(ast_rules[40][3],"expression");
	strcpy(ast_rules[40][4],"");

	ast_rules[41][0]=strcpy(ast_rules[41][0],"index");
	ast_rules[41][1]=strcpy(ast_rules[41][1],"->");
	ast_rules[41][2]=strcpy(ast_rules[41][2],"NUM");
	strcpy(ast_rules[41][3],"");

	ast_rules[42][0]=strcpy(ast_rules[42][0],"index");
	ast_rules[42][1]=strcpy(ast_rules[42][1],"->");
	ast_rules[42][2]=strcpy(ast_rules[42][2],"ID");
	strcpy(ast_rules[42][3],"");

	ast_rules[43][0]=strcpy(ast_rules[43][0],"moduleReuseStmt");
	ast_rules[43][1]=strcpy(ast_rules[43][1],"->");
	ast_rules[43][2]=strcpy(ast_rules[43][2],"optional");
	ast_rules[43][3]=strcpy(ast_rules[43][3],"ID");
	ast_rules[43][4]=strcpy(ast_rules[43][4],"idList");
	ast_rules[43][5]=strcpy(ast_rules[43][5],"");

	ast_rules[44][0] = strcpy(ast_rules[44][0],"optional");
	ast_rules[44][1] = strcpy(ast_rules[44][1],"->");
	ast_rules[44][2] = strcpy(ast_rules[44][2],"idList");
	ast_rules[44][3] = strcpy(ast_rules[44][3],"");

	ast_rules[45][0] = strcpy(ast_rules[45][0],"optional");
	ast_rules[45][1] = strcpy(ast_rules[45][1],"->");
	ast_rules[45][2] = strcpy(ast_rules[45][2],"#");
	strcpy(ast_rules[45][3],"");

	ast_rules[46][0] = strcpy(ast_rules[46][0],"idList");
	ast_rules[46][1] = strcpy(ast_rules[46][1],"->");
	ast_rules[46][2] = strcpy(ast_rules[46][2],"ID");
	ast_rules[46][3] = strcpy(ast_rules[46][3],"n3");
	strcpy(ast_rules[46][4],"");
	
	ast_rules[47][0] = strcpy(ast_rules[47][0],"n3");
	ast_rules[47][1] = strcpy(ast_rules[47][1],"->");
	ast_rules[47][2] = strcpy(ast_rules[47][2],"ID");
	ast_rules[47][3] = strcpy(ast_rules[47][3],"n3");
	ast_rules[47][4] = strcpy(ast_rules[47][4],"");

	ast_rules[48][0] = strcpy(ast_rules[48][0],"n3");
	ast_rules[48][1] = strcpy(ast_rules[48][1],"->");
	ast_rules[48][2] = strcpy(ast_rules[48][2],"#");
	strcpy(ast_rules[48][3],"");

	ast_rules[49][0] = strcpy(ast_rules[49][0],"declareStmt");
	ast_rules[49][1] = strcpy(ast_rules[49][1],"->");
	ast_rules[49][2] = strcpy(ast_rules[49][2],"idList");
	ast_rules[49][3] = strcpy(ast_rules[49][3],"dataType");
	ast_rules[49][4] = strcpy(ast_rules[49][4],"");
	
	ast_rules[50][0] = strcpy(ast_rules[50][0],"conditionalStmt");
	ast_rules[50][1] = strcpy(ast_rules[50][1],"->");
	ast_rules[50][2] = strcpy(ast_rules[50][2],"ID");
	ast_rules[50][3] = strcpy(ast_rules[50][3],"start");
	ast_rules[50][4] = strcpy(ast_rules[50][4],"caseStmts");
	ast_rules[50][5] = strcpy(ast_rules[50][5],"default");
	ast_rules[50][6] = strcpy(ast_rules[50][6],"end");
	ast_rules[50][7] = strcpy(ast_rules[50][7],"");
	
	ast_rules[51][0] = strcpy(ast_rules[51][0],"caseStmts");
	ast_rules[51][1] = strcpy(ast_rules[51][1],"->");
	ast_rules[51][2] = strcpy(ast_rules[51][2],"value");
	ast_rules[51][3] = strcpy(ast_rules[51][3],"statements");
	ast_rules[51][4] = strcpy(ast_rules[51][4],"n9");
	ast_rules[51][5] = strcpy(ast_rules[51][5],"");
	
	
	ast_rules[52][0] = strcpy(ast_rules[52][0],"n9");
	ast_rules[52][1] = strcpy(ast_rules[52][1],"->");
	ast_rules[52][2] = strcpy(ast_rules[52][2],"value");
	ast_rules[52][3] = strcpy(ast_rules[52][3],"statements");
	ast_rules[52][4] = strcpy(ast_rules[52][4],"n9");
	ast_rules[52][5] = strcpy(ast_rules[52][5],"");
		
	ast_rules[53][0] = strcpy(ast_rules[53][0],"n9");
	ast_rules[53][1] = strcpy(ast_rules[53][1],"->");
	ast_rules[53][2] = strcpy(ast_rules[53][2],"#");
	strcpy(ast_rules[53][3],"");
	
	ast_rules[54][0] = strcpy(ast_rules[54][0],"value");
	ast_rules[54][1] = strcpy(ast_rules[54][1],"->");
	ast_rules[54][2] = strcpy(ast_rules[54][2],"NUM");
	strcpy(ast_rules[54][3],"");

	ast_rules[55][0] = strcpy(ast_rules[55][0],"value");
	ast_rules[55][1] = strcpy(ast_rules[55][1],"->");
	ast_rules[55][2] = strcpy(ast_rules[55][2],"TRUE");
	strcpy(ast_rules[55][3],"");
	
	ast_rules[56][0] = strcpy(ast_rules[56][0],"value");
	ast_rules[56][1] = strcpy(ast_rules[56][1],"->");
	ast_rules[56][2] = strcpy(ast_rules[56][2],"FALSE");
	strcpy(ast_rules[56][3],"");
	
	ast_rules[57][0] = strcpy(ast_rules[57][0],"default");
	ast_rules[57][1] = strcpy(ast_rules[57][1],"->");
	ast_rules[57][2] = strcpy(ast_rules[57][2],"statements");
	ast_rules[57][3] = strcpy(ast_rules[57][3],"");
	
	ast_rules[58][0] = strcpy(ast_rules[58][0],"default");
	ast_rules[58][1] = strcpy(ast_rules[58][1],"->");
	ast_rules[58][2] = strcpy(ast_rules[58][2],"#");
	strcpy(ast_rules[58][3],"");
	
	ast_rules[59][0] = strcpy(ast_rules[59][0],"iterativeStmt");
	ast_rules[59][1] = strcpy(ast_rules[59][1],"->");
	ast_rules[59][2] = strcpy(ast_rules[59][2],"FOR");
	ast_rules[59][3] = strcpy(ast_rules[59][3],"ID");
	ast_rules[59][4] = strcpy(ast_rules[59][4],"NUM");
	ast_rules[59][5] = strcpy(ast_rules[59][5],"NUM");
	ast_rules[59][6] = strcpy(ast_rules[59][6],"start");
	ast_rules[59][7] = strcpy(ast_rules[59][7],"statements");
	ast_rules[59][8] = strcpy(ast_rules[59][8],"end");
	ast_rules[59][9] = strcpy(ast_rules[59][9],"");
	
	ast_rules[60][0] = strcpy(ast_rules[60][0],"iterativeStmt");
	ast_rules[60][1] = strcpy(ast_rules[60][1],"->");
	ast_rules[60][2] = strcpy(ast_rules[60][2],"WHILE");
	ast_rules[60][3] = strcpy(ast_rules[60][3],"arithmeticOrBooleanExpr");
	ast_rules[60][4] = strcpy(ast_rules[60][4],"start");
	ast_rules[60][5] = strcpy(ast_rules[60][5],"statements");
	ast_rules[60][6] = strcpy(ast_rules[60][6],"end");
	ast_rules[60][7] = strcpy(ast_rules[60][7],"");

	ast_rules[61][0]=strcpy(ast_rules[61][0],"expression");
	ast_rules[61][1]=strcpy(ast_rules[61][1],"->");
	ast_rules[61][2]=strcpy(ast_rules[61][2],"arithmeticOrBooleanExpr");
	strcpy(ast_rules[61][3],"");
	
	ast_rules[62][0]=strcpy(ast_rules[62][0],"expression");
	ast_rules[62][1]=strcpy(ast_rules[62][1],"->");
	ast_rules[62][2]=strcpy(ast_rules[62][2],"u");
	strcpy(ast_rules[62][3],"");
	
	ast_rules[63][0]=strcpy(ast_rules[63][0],"u");
	ast_rules[63][1]=strcpy(ast_rules[63][1],"->");
	ast_rules[63][2]=strcpy(ast_rules[63][2],"unary_op");
	ast_rules[63][3]=strcpy(ast_rules[63][3],"new_NT");
	strcpy(ast_rules[63][4],"");
	

	ast_rules[64][0]=strcpy(ast_rules[64][0],"new_NT");
	ast_rules[64][1]=strcpy(ast_rules[64][1],"->");
	ast_rules[64][2]=strcpy(ast_rules[64][2],"var_id_num");
	strcpy(ast_rules[64][3],"");
	    
	ast_rules[65][0]=strcpy(ast_rules[65][0],"new_NT");
	ast_rules[65][1]=strcpy(ast_rules[65][1],"->");
	ast_rules[65][2]=strcpy(ast_rules[65][2],"arithmeticExpr");
	ast_rules[65][3]=strcpy(ast_rules[65][3],"");

	ast_rules[66][0]=strcpy(ast_rules[66][0],"unary_op");
	ast_rules[66][1]=strcpy(ast_rules[66][1],"->");
	ast_rules[66][2]=strcpy(ast_rules[66][2],"PLUS");
	strcpy(ast_rules[66][3],"");
	
	ast_rules[67][0]=strcpy(ast_rules[67][0],"unary_op");
	ast_rules[67][1]=strcpy(ast_rules[67][1],"->");
	ast_rules[67][2]=strcpy(ast_rules[67][2],"MINUS");
	strcpy(ast_rules[67][3],"");
	
	
	ast_rules[68][0]=strcpy(ast_rules[68][0],"arithmeticOrBooleanExpr");
	ast_rules[68][1]=strcpy(ast_rules[68][1],"->");
	ast_rules[68][2]=strcpy(ast_rules[68][2],"anyTerm");
	ast_rules[68][3]=strcpy(ast_rules[68][3],"n7");
	strcpy(ast_rules[68][4],"");
	
	ast_rules[69][0]=strcpy(ast_rules[69][0],"n7");
	ast_rules[69][1]=strcpy(ast_rules[69][1],"->");
	ast_rules[69][2]=strcpy(ast_rules[69][2],"logicalOp");
	ast_rules[69][3]=strcpy(ast_rules[69][3],"anyTerm");
	ast_rules[69][4]=strcpy(ast_rules[69][4],"n7");
	strcpy(ast_rules[69][5],"");
	
	ast_rules[70][0]=strcpy(ast_rules[70][0],"n7");
	ast_rules[70][1]=strcpy(ast_rules[70][1],"->");
	ast_rules[70][2]=strcpy(ast_rules[70][2],"#");
	strcpy(ast_rules[70][3],"");
	
	ast_rules[71][0]=strcpy(ast_rules[71][0],"anyTerm");
	ast_rules[71][1]=strcpy(ast_rules[71][1],"->");
	ast_rules[71][2]=strcpy(ast_rules[71][2],"arithmeticExpr");
	ast_rules[71][3]=strcpy(ast_rules[71][3],"n8");
	strcpy(ast_rules[71][4],"");

	ast_rules[72][0]=strcpy(ast_rules[72][0],"anyTerm");
	ast_rules[72][1]=strcpy(ast_rules[72][1],"->");
	ast_rules[72][2]=strcpy(ast_rules[72][2],"boolConstt");
	strcpy(ast_rules[72][3],"");
	
	ast_rules[73][0]=strcpy(ast_rules[73][0],"n8");
	ast_rules[73][1]=strcpy(ast_rules[73][1],"->");
	ast_rules[73][2]=strcpy(ast_rules[73][2],"relationalOp");
	ast_rules[73][3]=strcpy(ast_rules[73][3],"arithmeticExpr");
	strcpy(ast_rules[73][4],"");

	ast_rules[74][0] = strcpy(ast_rules[74][0],"relationalOp");
	ast_rules[74][1] = strcpy(ast_rules[74][1],"->");
	ast_rules[74][2] = strcpy(ast_rules[74][2],"NE");
	strcpy(ast_rules[74][3],"");
		
	ast_rules[75][0]=strcpy(ast_rules[75][0],"n8");
	ast_rules[75][1]=strcpy(ast_rules[75][1],"->");
	ast_rules[75][2]=strcpy(ast_rules[75][2],"#");
	strcpy(ast_rules[75][3],"");
	
	ast_rules[76][0] = strcpy(ast_rules[76][0],"arithmeticExpr");
	ast_rules[76][1] = strcpy(ast_rules[76][1],"->");
	ast_rules[76][2] = strcpy(ast_rules[76][2],"term");
	ast_rules[76][3] = strcpy(ast_rules[76][3],"n4");
	strcpy(ast_rules[76][4],"");

	ast_rules[77][0] = strcpy(ast_rules[77][0],"n4");
	ast_rules[77][1] = strcpy(ast_rules[77][1],"->");
	ast_rules[77][2] = strcpy(ast_rules[77][2],"op1");
	ast_rules[77][3] = strcpy(ast_rules[77][3],"term");
	ast_rules[77][4] = strcpy(ast_rules[77][4],"n4");
	strcpy(ast_rules[77][5],"");
	
	ast_rules[78][0] = strcpy(ast_rules[78][0],"n4");
	ast_rules[78][1] = strcpy(ast_rules[78][1],"->");
	ast_rules[78][2] = strcpy(ast_rules[78][2],"#");
	strcpy(ast_rules[78][3],"");
	
	
	
	ast_rules[79][0] = strcpy(ast_rules[79][0],"term");
	ast_rules[79][1] = strcpy(ast_rules[79][1],"->");
	ast_rules[79][2] = strcpy(ast_rules[79][2],"factor");
	ast_rules[79][3] = strcpy(ast_rules[79][3],"n5");
	strcpy(ast_rules[79][4],"");
	
	ast_rules[80][0] = strcpy(ast_rules[80][0],"n5");
	ast_rules[80][1] = strcpy(ast_rules[80][1],"->");
	ast_rules[80][2] = strcpy(ast_rules[80][2],"op2");
	ast_rules[80][3] = strcpy(ast_rules[80][3],"factor");
	ast_rules[80][4] = strcpy(ast_rules[80][4],"n5");
	strcpy(ast_rules[80][5],"");
	
	ast_rules[81][0] = strcpy(ast_rules[81][0],"n5");
	ast_rules[81][1] = strcpy(ast_rules[81][1],"->");
	ast_rules[81][2] = strcpy(ast_rules[81][2],"#");
	strcpy(ast_rules[81][3],"");
	
	ast_rules[82][0] = strcpy(ast_rules[82][0],"factor");
	ast_rules[82][1] = strcpy(ast_rules[82][1],"->");
	ast_rules[82][2] = strcpy(ast_rules[82][2],"BO");
	ast_rules[82][3] = strcpy(ast_rules[82][3],"arithmeticOrBooleanExpr");
	ast_rules[82][4] = strcpy(ast_rules[82][4],"BC");
	strcpy(ast_rules[82][5],"");
	
	ast_rules[83][0] = strcpy(ast_rules[83][0],"factor");
	ast_rules[83][1] = strcpy(ast_rules[83][1],"->");
	ast_rules[83][2] = strcpy(ast_rules[83][2],"var_id_num");
	strcpy(ast_rules[83][3],"");

	ast_rules[84][0] = strcpy(ast_rules[84][0],"op1");
	ast_rules[84][1] = strcpy(ast_rules[84][1],"->");
	ast_rules[84][2] = strcpy(ast_rules[84][2],"PLUS");
	strcpy(ast_rules[84][3],"");

	ast_rules[85][0] = strcpy(ast_rules[85][0],"op1");
	ast_rules[85][1] = strcpy(ast_rules[85][1],"->");
	ast_rules[85][2] = strcpy(ast_rules[85][2],"MINUS");
	strcpy(ast_rules[85][3],"");

	ast_rules[86][0] = strcpy(ast_rules[86][0],"op2");
	ast_rules[86][1] = strcpy(ast_rules[86][1],"->");
	ast_rules[86][2] = strcpy(ast_rules[86][2],"MUL");
	strcpy(ast_rules[86][3],"");

	ast_rules[87][0] = strcpy(ast_rules[87][0],"op2");
	ast_rules[87][1] = strcpy(ast_rules[87][1],"->");
	ast_rules[87][2] = strcpy(ast_rules[87][2],"DIV");
	strcpy(ast_rules[87][3],"");

	ast_rules[88][0] = strcpy(ast_rules[88][0],"logicalOp");
	ast_rules[88][1] = strcpy(ast_rules[88][1],"->");
	ast_rules[88][2] = strcpy(ast_rules[88][2],"AND");
	strcpy(ast_rules[88][3],"");

	ast_rules[89][0] = strcpy(ast_rules[89][0],"logicalOp");
	ast_rules[89][1] = strcpy(ast_rules[89][1],"->");
	ast_rules[89][2] = strcpy(ast_rules[89][2],"OR");
	strcpy(ast_rules[89][3],"");

	ast_rules[90][0] = strcpy(ast_rules[90][0],"relationalOp");
	ast_rules[90][1] = strcpy(ast_rules[90][1],"->");
	ast_rules[90][2] = strcpy(ast_rules[90][2],"LE");
	strcpy(ast_rules[90][3],"");

	ast_rules[91][0] = strcpy(ast_rules[91][0],"relationalOp");
	ast_rules[91][1] = strcpy(ast_rules[91][1],"->");
	ast_rules[91][2] = strcpy(ast_rules[91][2],"GE");
	strcpy(ast_rules[91][3],"");

	ast_rules[92][0] = strcpy(ast_rules[92][0],"relationalOp");
	ast_rules[92][1] = strcpy(ast_rules[92][1],"->");
	ast_rules[92][2] = strcpy(ast_rules[92][2],"LT");
	strcpy(ast_rules[92][3],"");

	ast_rules[93][0] = strcpy(ast_rules[93][0],"relationalOp");
	ast_rules[93][1] = strcpy(ast_rules[93][1],"->");
	ast_rules[93][2] = strcpy(ast_rules[93][2],"GT");
	strcpy(ast_rules[93][3],"");

	ast_rules[94][0] = strcpy(ast_rules[94][0],"relationalOp");
	ast_rules[94][1] = strcpy(ast_rules[94][1],"->");
	ast_rules[94][2] = strcpy(ast_rules[94][2],"EQ");
	strcpy(ast_rules[94][3],"");

}

	


















