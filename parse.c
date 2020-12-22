/*
2017A7PS0133P M VENKAT SAI RAM
2017A7PS0079P ABHISHEK BHARADWAJ
2017A7PS0144P K SAI KISHORE3-7.87
2017A7PS0141P B HARI KISHORE
2017A7PS0154P G SAI SARATH KRISHNA

GROUP NUMBER 45
*/
#include "parseTree.h"



PARSE_NODE parsetable[PT_ROWS][PT_COLUMNS];

char * err;
char * sy;
char **error;
char **syn;
int t_count;
int createParseTable(int m,int n,int a,int b)
{
    err="error";
    sy="syn";
    error=&err;
    syn=&sy;
    int i,j;
    for(i=0;i<PT_ROWS;i++)
        for(j=0;j<PT_COLUMNS;j++)
        {
            parsetable[i][j].rule=NULL;
            parsetable[i][j].symbol=NULL;
        }
	//sprintf("%s\n",calc_first[m][0]);

    for(i=0;i<m;i++)
    {
        parsetable[i+1][0].symbol=calc_first[i][0];
        parsetable[i+1][0].rule=NULL;
        //printf(" %s \n",parsetable[i+1][0].symbol);
    }

    int s=1;
    int check=0;
    int p=0;
    int t=1;
    int k;

    for(i=0;i<a;i++)
    {
        for(j=2;strcmp(production[i][j],"");j++)
        {
            if(isupper(production[i][j][0]))
            {
                for(k=1;k<s;k++)
                {
                    if(strcmp(parsetable[0][k].symbol,production[i][j])==0)
                        check=1;

                }
                if(check!=1)
                {
                    parsetable[0][s].symbol=(parsetable[0][s].symbol,production[i][j]);
                    s++;
                   // printf("%d %s\n",s-1,parsetable[0][s-1].symbol);


                }
                check=0;

            }

        }
    }
    char *str="$";
    parsetable[0][s].symbol =str;
    //printf("%d %s\n",s,parsetable[0][s].symbol);
    s++;



    for(int i=1;i<m+1;i++)
    {
        for(int j=0;j<a;j++)
        {
            if(strcmp(parsetable[i][0].symbol,production[j][0])==0)
            {
		//printf("%s \n",production[j][0]);		
		if(strcmp(production[j][2],"#")!=0)
                {
			for(k=1;k<s;k++)
			{				
				for(int x=2;strcmp(production[j][x],"")!=0;x++)
				{	
					if(isupper(production[j][x][0]))
					{
						if(strcmp((parsetable[0][k].symbol),production[j][x])==0)
							parsetable[i][k].rule=production[j];
						break;		
					}					
					else
					{
						if(isInFirst(production[j][x],parsetable[0][k].symbol))
							parsetable[i][k].rule=production[j];
						if(isInFirst(production[j][x],"#"))
							continue;						
						break;
					}
				}
			}
		}
                else
                {
                     for(p=0;p<m;p++)
                     {
                       if(strcmp(calc_follow[p][0],production[j][0])==0)
                       {
                           for(t=1;strcmp(calc_follow[p][t],"!")!=0;t++)
                           {
                               for(k=1;k<s;k++)
                               {
                                   if(strcmp(parsetable[0][k].symbol,calc_follow[p][t])==0)
                                        parsetable[i][k].rule=production[j];

                                }
                           }
                       }
                     }
                }
            }
        }
    }


    for(int i=0;i<m;i++)
    {
        for (int j=1;strcmp(calc_follow[i][j],"!")!=0;j++)
        {
            for(int k=1;parsetable[0][k].symbol!=NULL;k++)
                {
                    if(strcmp(parsetable[0][k].symbol,calc_follow[i][j])==0)
                        if(parsetable[i+1][k].rule==NULL)
                            {
                                parsetable[i+1][k].rule=syn;
                            }
                }
        }
    }

    printf("%d",s);
    for(int i=1;i<PT_ROWS;i++)
    for(int j=1;j<s;j++)
    if(parsetable[i][j].rule==NULL)
    {
	parsetable[i][j].rule=error;
	//printf("%d %d  ",i,j);
    }
	t_count=s;
	//printParseTable(s);
	return s;
}
 
    

 /*   for (int i=1;i<m+1;i++)
       printf("%s \n",parsetable[i][0].symbol);
    printf("\n");

     for(int j=1;j<s;j++)
       printf("%s \n",parsetable[0][j].symbol);
*/

    // printf("%d\n",s);
    /*for(int p=0; ((parsetable[1][1].rule)[p],""))!=0;p++)
     printf("%s ",(parsetable[1][1].rule)[p]); */

/*    int d=0;
    for (int i=1;i<m+1;i++)
    {
       for (int j=1;j<s;j++)
       {
           if(strcmp(*(parsetable[i][j].rule),*error)==0)
           {
               printf("%s \n",*error);
           }
           else if(strcmp(*(parsetable[i][j].rule),*syn)==0)
           {
               printf("%s \n",*syn);
           }
           else
           {

               while( strcmp((parsetable[i][j].rule)[d],"")!=0)
               {

                   printf("%s  ",(parsetable[i][j].rule)[d]);
                   d++;
               }
               d=0;
               printf("\n");
           }
       }
       printf("\n\n\n");
    }

	return s;
}
*/


    /*
int main()
{
    int i,j=0;
    char * grammar[5][8];
    for(i=0;i<5;i++)
        for(j=0;j<8;j++)
            grammar[i][j]=(char *)malloc(sizeof(char)*15);


grammar[0][0] = strcpy(grammar[0][0],"optional");
grammar[0][1] = strcpy(grammar[0][1],"->");
grammar[0][2] = strcpy(grammar[0][2],"SQBO");
grammar[0][3] = strcpy(grammar[0][3],"idList");
grammar[0][4] = strcpy(grammar[0][4],"SQBC");
grammar[0][5] = strcpy(grammar[0][5],"ASSIGNOP");
grammar[0][6] = strcpy(grammar[0][6],"");
grammar[0][7] =NULL;

grammar[1][0] = strcpy(grammar[1][0],"optional");
grammar[1][1] = strcpy(grammar[1][1],"->");
grammar[1][2] = strcpy(grammar[1][2],"#");
grammar[1][3] = strcpy(grammar[1][3],"");
grammar[1][4] = NULL;
grammar[1][5] = NULL;
grammar[1][6] = NULL;
grammar[1][7] =NULL;

grammar[2][0] = strcpy(grammar[2][0],"idList");
grammar[2][1] = strcpy(grammar[2][1],"->");
grammar[2][2] = strcpy(grammar[2][2],"ID");
grammar[2][3] = strcpy(grammar[2][3],"n3");
grammar[2][4] = strcpy(grammar[2][4],"");
grammar[2][5] = NULL;
grammar[2][6] = NULL;
grammar[2][7] =NULL;

grammar[3][0] = strcpy(grammar[3][0],"n3");
grammar[3][1] = strcpy(grammar[3][1],"->");
grammar[3][2] = strcpy(grammar[3][2],"COMMA");
grammar[3][3] = strcpy(grammar[3][3],"ID");
grammar[3][4] = strcpy(grammar[3][4],"n3");
grammar[3][5] = strcpy(grammar[3][5],"");
grammar[3][6] = NULL;
grammar[3][7] =NULL;

grammar[4][0] = strcpy(grammar[4][0],"n3");
grammar[4][1] = strcpy(grammar[4][1],"->");
grammar[4][2] = strcpy(grammar[4][2],"#");
grammar[4][3] = strcpy(grammar[4][3],"");
grammar[4][4] = NULL;
grammar[4][5] = NULL;
grammar[4][6] = NULL;
grammar[4][7] =NULL;



char *first[3][4];
char * follow[3][4];


for(i=0;i<3;i++)
    for(j=0;j<4;j++)
        first[i][j]=(char *)malloc(sizeof(char)*15);

for(i=0;i<3;i++)
    for(j=0;j<4;j++)
        follow[i][j]=(char *)malloc(sizeof(char)*15);


first[0][0]=strcpy(first[0][0],"optional");
first[0][1]=strcpy(first[0][1],"SQBO");
first[0][2]=strcpy(first[0][2],"#");
first[0][3]=strcpy(first[0][3],"!");

first[1][0]=strcpy(first[1][0],"idList");
first[1][1]=strcpy(first[1][1],"ID");
first[1][2]=strcpy(first[1][2],"!");
first[1][3]=NULL;

first[2][0]=strcpy(first[2][0],"n3");
first[2][1]=strcpy(first[2][1],"COMMA");
first[2][2]=strcpy(first[2][2],"#");
first[2][3]=strcpy(first[2][3],"!");

follow[0][0]=strcpy(follow[0][0],"optional");
follow[0][1]=strcpy(follow[0][1],"$");
follow[0][2]=strcpy(follow[0][2],"!");
follow[0][3]=NULL;

follow[1][0]=strcpy(follow[1][0],"idList");
follow[1][1]=strcpy(follow[1][1],"SQBC");
follow[1][2]=strcpy(follow[1][2],"!");
follow[1][3]=NULL;

follow[2][0]=strcpy(follow[2][0],"n3");
follow[2][1]=strcpy(follow[2][1],"SQBC");
follow[2][2]=strcpy(follow[2][2],"!");
follow[2][3]=NULL;


for(i=0;i<5;i++)
{
    for(j=0;j<8;j++)
    {
        printf("%s ",grammar[i][j]);
    }
    printf("\n");
}







//PARSE_NODE** parsetable[10][10];
createParseTable(3,4,5,8,first,follow,grammar);


}
*/

/*  

 for(int i=1;i<m+1;i++)
    {
        for(int j=0;j<a;j++)
        {
            if(strcmp(parsetable[i][0].symbol,production[j][0])==0)
            {
                if(isupper(production[j][2][0]))
                {
                    for(k=1;k<s;k++)
                    {
                        if(strcmp(production[j][2],parsetable[0][k].symbol)==0)
                            parsetable[i][k].rule=production[j];
                    }
                }
                else if(strcmp(production[j][2],"#")!=0)
                {
                   for(p=0;p<m;p++)
                   {
                       if(strcmp(calc_first[p][0],production[j][2])==0)
                       {
                           for(t=1;strcmp(calc_first[p][t],"!")!=0;t++)
                           {
                               for(k=1;k<s;k++)
                               {
                                   if(strcmp(parsetable[0][k].symbol,calc_first[p][t])==0)
                                        parsetable[i][k].rule=production[j];
                               }
                           }
                       }
                   }
                }
                else
                {
                     for(p=0;p<m;p++)
                     {
                       if(strcmp(calc_follow[p][0],production[j][0])==0)
                       {
                           for(t=1;strcmp(calc_first[p][t],"!")!=0;t++)
                           {
                               for(k=1;k<s;k++)
                               {
                                   if(strcmp(parsetable[0][k].symbol,calc_follow[p][t])==0)
                                        parsetable[i][k].rule=production[j];

                                }
                           }
                       }
                     }
                }
            }
        }
    }

*/
