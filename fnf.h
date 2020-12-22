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
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define RULECOUNT 105
#define NTCOUNT 57
#define COLUMNS 15
#define NTCOL 250
#define NTCOLS 20


void computeFirstAndFollowSets();
void initializeProductions();
void followfirst(char*, int, int);
void follow(char* c);
void printFirstAndFollowSets();
void findfirst(char*, int, int);
char *** getGrammar();
void printGrammar(char***);
int isInFirst(char *nt,char *ter);
int isInFollow(char *nt,char *ter);

extern int count , n , m, column;
extern char *calc_first[NTCOUNT][NTCOLS];
extern char *calc_follow[NTCOUNT][NTCOLS];
extern char ***production;
extern char *f[NTCOL], *first[NTCOL];
extern char *ck;



//#endif
