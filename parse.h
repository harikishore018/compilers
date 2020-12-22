
/*
2017A7PS0133P M VENKAT SAI RAM
2017A7PS0079P ABHISHEK BHARADWAJ
2017A7PS0144P K SAI KISHORE
2017A7PS0141P B HARI KISHORE
2017A7PS0154P G SAI SARATH KRISHNA

GROUP NUMBER 45
*/

#define PT_ROWS 60
#define PT_COLUMNS 60
#include "fnf.h"
typedef struct parseNode
{
    char *symbol;
    char **rule;
}PARSE_NODE;

extern int t_count;
extern PARSE_NODE parsetable[PT_ROWS][PT_COLUMNS];

extern char * err;
extern char * sy;
extern char **error;
extern char **syn;



int createParseTable(int m,int n,int a,int b);



