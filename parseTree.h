//#ifndef HELLO_WORLD_H
//#define HELLO_WORLD_H
/*
2017A7PS0133P M VENKAT SAI RAM
2017A7PS0079P ABHISHEK BHARADWAJ
2017A7PS0144P K SAI KISHORE
2017A7PS0141P B HARI KISHORE
2017A7PS0154P G SAI SARATH KRISHNA

GROUP NUMBER 45
*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "parse.h"
#include "lexer.h"
#define PT_ROWS 60
#define PT_COLUMNS 60
#define GRAMMAR_LEN 20


typedef enum 
{
grammar, moduleDeclarations, moduleDeclaration, otherModules, driverModule, module, ret, 
input_plist, n1, output_plist, n2, dataType, range_arrays, type, moduleDef, statements, statement, 
ioStmt, boolConstt, var_id_num, var, whichID, simpleStmt, assignmentStmt, whichStmt, lvalueIDStmt, lvalueARRStmt, 
index_nt, moduleReuseStmt, optional, idList, n3, expression, u, new_NT, unary_op, arithmeticOrBooleanExpr, n7, 
anyTerm, n8, arithmeticExpr, n4, term_nt, n5, factor, op1, op2, logicalOp, relationalOp, 
declareStmt, conditionalStmt, caseStmts, n9, value, default_1, iterativeStmt, range
}non_term;

typedef enum{
DECLARE, MODULE, ID, SEMICOL, DRIVERDEF, DRIVER, PROGRAM, DRIVERENDDEF, DEF, ENDDEF, TAKES,
INPUT, SQBO, SQBC, RETURNS, COLON, COMMA, ARRAY, OF, RANGEOP, INTEGER, REAL, BOOLEAN, START, END, GET_VALUE, 
BO, BC, PRINT, TRUE, FALSE, NUM, RNUM, ASSIGNOP, USE, WITH, PARAMETERS, PLUS, MINUS, MUL,
DIV, AND, OR, LT, LE, GT, GE, EQ, NE, SWITCH, CASE, BREAK, DEFAULT, FOR, IN, WHILE, $,e, null_point = -1
}term;

struct tokenInfo 
{
	term s;
	char *lex;
	int lno;		
};

typedef struct tokenInfo tokenInfo;

typedef union
{
	term t;
	non_term nt;
}gElement;

typedef enum {terminal, non_terminal} tag;

typedef struct pNode *pNode;
typedef struct Queue Queue;

struct Queue
{
	pNode front;
	pNode back;
	int size;
};

struct pNode
{
	tag t;
	gElement e;
	char *tok;
	int no_of_child;
	tokenInfo* token_link;
	pNode next;
	pNode parent;
	pNode node[GRAMMAR_LEN]; 
	Queue child;
};

struct parseTree
{
	pNode root;
	pNode c_node;
	int height;
};
typedef struct parseTree parseTree;

typedef struct treeNode
{
	int t;	
	char *lex;  
	char *tok;  
	//LEXER *info_t;   	
	int line_no;
	struct treeNode *parent;
	int node_num;
	int c_count;
	struct treeNode *sibling; 
	struct treeNode *node[GRAMMAR_LEN]; 
} NODE;


extern PARSE_NODE parsetable1[PT_ROWS][PT_COLUMNS];
extern int syn_err;

extern int node_count;    
extern NODE *head;
extern pNode phead;

void createNewParseTree();
void createASTParseTree(pNode phead,NODE *head);
int calculateT(char *tok);
int calculateNT(char *tok);
void printASTParseTree(pNode phead);
void printASTDetails(pNode phead);

int parseResult(char **stack,int top,int err);
void printStack(int top,char **stack);
void printParseTable(int s);
void parseTreeCall(char *argv,int s);
BLOCK *initializer(char *argv);
int stackBuild(char **rule,int top,char **stack);
int push(int top,char **stack,char **rule);
int pop(int top,char **stack);
int parser(BLOCK *bl);
NODE *buildParseTree(char **rule,NODE *cur,LEXER *lr);
void printParseTree(NODE *head);
void printDetails(NODE *head);


//#endif


