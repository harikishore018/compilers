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
#define TABLE_SIZE 40

typedef struct sym_entry
{
    char *lexeme;
    char *token;
    struct sym_entry * next;
} SYM_ENTRY;

typedef struct table_entry
{
    SYM_ENTRY *first;
    int len;
} TABLE;

typedef struct st
{
    FILE *fp;
    char *stream;
    int len;
} BLOCK;

typedef struct lexer_return
{
    char *lex;
    char *tok;
    int line_no;
    struct lexer_return *next;
} LEXER;

extern TABLE hashTable[TABLE_SIZE];                 // create memory for hash table in main()
extern int line_num;
extern int *line_tok;
extern int line_count;
extern LEXER **tok_arr;
extern int tok_arr_size;


void lexerCall1(char *argv);
void printTokens();
void tokInitializer(LEXER *lr);
void showLineTok();
void printFile(char *argv,int x);
int computeIndex(char * lexeme);
void insert(SYM_ENTRY *entry);
char * search(char *lex);
void symTableDisplay();
void insertKeywords();
BLOCK *getStream(BLOCK *bl);
LEXER *getNextToken(BLOCK *bl);
void removeComments(FILE *fp1, FILE *cleanFile);
int commentFinder(FILE *fp);
void reportError(char *lex);
int isNum(char ch);
int isAlphabet(char ch);
void lexerCall(char *argv);

