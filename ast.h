/*
2017A7PS0133P M VENKAT SAI RAM
2017A7PS0079P ABHISHEK BHARADWAJ
2017A7PS0144P K SAI KISHORE
2017A7PS0141P B HARI KISHORE
2017A7PS0154P G SAI SARATH KRISHNA

GROUP NUMBER 45
*/


#include "parseTree.h"
#define AST_RULECOUNT 95

typedef struct ast_tree_node
{
	struct ast_tree_node *child;
	struct ast_tree_node *parent;
	struct ast_tree_node *left;
	struct ast_tree_node *right;
	char *value;
	char *tok;
} AST_NODE;

/*
	ast_head=(AST_NODE *)calloc(1,sizeof(AST_NODE));
	ast_head->parent=NULL;
	ast_head->left=NULL;
	ast_head->right=NULL;
	ast_head->value=NULL;
	ast_head->tok=head->tok;	
	NODE *temp=head;
	AST_NODE *cur=ast_head;
*/


extern char ***ast_rules;
extern AST_NODE *ast_head;
extern int ast_node_count;

AST_NODE *createNew();
void astCreateCall(NODE *head);
int isRequired (char *tok);
void printASTTreeDetails(NODE *head);
void ast_constrcution();
void populateAst(int index,AST_NODE *cur,NODE *present);
void createAstRules();

