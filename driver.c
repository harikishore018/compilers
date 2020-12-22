/*
2017A7PS0133P M VENKAT SAI RAM
2017A7PS0079P ABHISHEK BHARADWAJ
2017A7PS0144P K SAI KISHORE
2017A7PS0141P B HARI KISHORE
2017A7PS0154P G SAI SARATH KRISHNA

GROUP NUMBER 45
*/

#include "ast.h"
#include <time.h>
void timeTaken(char *argv,int s);
void timeTaken(char *argv,int s){
                clock_t    start_time, end_time;

                double total_CPU_time, total_CPU_time_in_seconds;

                start_time = clock();

                     parseTreeCall(argv,s);                          // invoke your lexer and parser here

                end_time = clock();

                total_CPU_time  =  (double) (end_time - start_time);

                total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
			
		    printf("Total CPU time = %lf\n",total_CPU_time);
		    printf("Total CPU time in seconds = %lf\n",total_CPU_time_in_seconds);  	
             // Print both total_CPU_time and total_CPU_time_in_seconds 
             }
int main(int argc,char **argv)
{
   
    int x,y,choice;
    char ***grammar = (char***)malloc(sizeof(char**)*RULECOUNT);
	double compression;
    printf("The lexical Analyser part along with the automatic computation of the first and follow sets, and the parse table has been implemented.The parser does complete analysis of the syntactic correctness of the code and generates a parse tree.The AST code is generated from the parse Tree generated the other parts are not implemented completely.So they dont give results\n ");
    for(x=0;x<RULECOUNT;x++)
        {
            grammar[x] = (char**) malloc(sizeof(char*) * COLUMNS);
            for(y=0;y<COLUMNS;y++)
                grammar[x][y] = (char*) malloc(sizeof(char) * 25);
        }
	
	insertKeywords();
	//lexerCall1(argv[1]);
	//line_num = 1;
	//printTokens();

	//printFile(argv[1],1);
	//showLineTok();  

//	printf("\n 1\n");
	initializeProductions();
  //      printf("\n 1\n");
	//printGrammar(production);
	//printf("\n 1\n");
	computeFirstAndFollowSets();
	//printf("\n 1\n");
	//printFirstAndFollowSets(); 	
	int s=createParseTable(NTCOUNT,NTCOLS,RULECOUNT,COLUMNS); 
	//printf("\n s is %d \n",s);
	
	/*lexerCall1(argv[1]);
	line_num = 1; */
	//printParseTable(s);
	//printTokens();
  
    //parseTreeCall();
    //lexerCall();
    while(1){
    printf("Press option (0-5) for the defined task\n");
    scanf("%d",&choice);
    switch(choice){
    case 0:	return 0;
    break;
    case 1: { 
		lexerCall(argv[1]);
		 line_num = 1;
              	}
    break;
    case 2: {
		parseTreeCall(argv[1],s);
		createNewParseTree();
		    line_num = 1;
		printParseTree(head);
		if(syn_err!=0)
			printf("\nThe program is syntactically incorrect. \n");	
	        else 
		        printf("\n The program is syntactically correct.\n");
		}
    break;
    case 3: {
		ast_node_count=0;		
		printf("\nThe AST Tree for the given text filw :\n\n");
		astCreateCall(head);
		printf(" #(otherModules)\n");
	}
    break;
    case 4: {
		printf("No. of Nodes in Parse Tree : %d \n",node_count);
		printf("Amount of memory allocated for the Parse Tree : %ld \n",node_count*sizeof(NODE));
		printf("No. of Nodes in the Abstract Syntax Tree : %d \n",ast_node_count);
		printf("Amount of memory allocated for the Abstract  Syntax Tree : %ld \n",ast_node_count*sizeof(AST_NODE));
		compression=((node_count*sizeof(NODE))-(ast_node_count*sizeof(AST_NODE)))*100.0/(node_count*sizeof(NODE));
		printf("Compression percentage = %lf\n",compression);
			}
    break;
    case 5: printf("\nThis module is not yet implemented completely and gives a segmentation fault\n");
    break;
    case 6: printf("\nThis module is not yet implemented completely and gives a segmentation fault\n");
    break;
    case 7: printf("\nThis module is not yet implemented completely and gives a segmentation fault\n");
    break;    	
    case 8: printf("\nThis module is not yet implemented completely and gives a segmentation fault\n");
            break;
    case 9:
	    printf("\nThis module is not yet implemented completely and gives a segmentation fault\n");	
    default: printf("Choose a number between 0 and 5 (both inclusive)\n");
    }
}    
}
