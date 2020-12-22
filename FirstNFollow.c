/*
2017A7PS0133P M VENKAT SAI RAM
2017A7PS0079P ABHISHEK BHARADWAJ
2017A7PS0144P K SAI KISHORE
2017A7PS0141P B HARI KISHORE
2017A7PS0154P G SAI SARATH KRISHNA

GROUP NUMBER 45
*/
#include "fnf.h"
char *calc_first[NTCOUNT][NTCOLS];
char *calc_follow[NTCOUNT][NTCOLS];
char ***production;
char *f[NTCOL], *first[NTCOL];
char *ck;
int m = 0;
int count = RULECOUNT, n = 0, column=COLUMNS;


int isInFirst(char *nt,char *ter)
{
	//printf(" Entered isInFirst \n");	
	for(int i=0;i<NTCOUNT;i++)
		if(strcmp(calc_first[i][0],nt)==0)
			for(int j=1;j<NTCOLS&&(strcmp(calc_first[i][j],"!")!=0);j++)
				if(strcmp(calc_first[i][j],ter)==0)
					return 1;	
	return 0;
}
			
int isInFollow(char *nt,char *ter)
{
	for(int i=0;i<NTCOUNT;i++)
		if(strcmp(calc_follow[i][0],nt)==0)
			for(int j=1;j<NTCOLS&&(strcmp(calc_follow[i][j],"!")!=0);j++)
				if(strcmp(calc_follow[i][j],ter)==0)
					return 1;
	return 0;
}


void follow(char *c)
{
	int i, j;

	// Adding "$" to the follow
	// set of the start symbol
	if(!strcmp(production[0][0], c)) {
		strcpy(f[m++], "$");
	}
	for(i = 0; i < count; i++)
	{   //printf("1");
		for(j = 2;j < column; j++)
		{  // printf("%d %d %s\n",i, j, c);
			if(!strcmp(production[i][j], c))
			{
				//printf("1");
				if(strcmp(production[i][j+1],"" ))
				{
					// Calculate the first of the next
					// Non-Terminal in the production
					//printf("%d %d",i , j);
					//printf("1");
					followfirst(production[i][j+1], i, (j+2));
				}

				if(!strcmp(production[i][j+1],"") && strcmp(c,production[i][0]))
				{
					// Calculate the follow of the Non-Terminal
					// in the L.H.S. of the production
					//printf("hey");
					follow(production[i][0]);
				}
			}
		}
	}
}

void findfirst(char *c, int q1, int q2)
{
	int j;

	// The case where we
	// encounter a Terminal
	if((isupper(c[0]))) {
		strcpy(first[n++], c);
	}
	for(j = 0; j < count; j++)
	{
		if(!strcmp(production[j][0], c))
		{
			if(!strcmp(production[j][2],"#"))
			{
				if(!strcmp(production[q1][q2],""))
					strcpy(first[n++],"#");
				else if(strcmp(production[q1][q2], "")
						&& (q1 != 0 || q2 != 0))
				{
					// Recursion to calculate First of New
					// Non-Terminal we encounter after epsilon
					findfirst(production[q1][q2], q1, (q2+1));
				}
				else
					strcpy(first[n++],"#");
			}
			else if(isupper(production[j][2][0]))
			{
				strcpy(first[n++], production[j][2]);
			}
			else
			{
				// Recursion to calculate First of
				// New Non-Terminal we encounter
				// at the beginning
				findfirst(production[j][2], j, 3);
			}
		}
	}
}

void followfirst(char *c, int c1, int c2)
{

	// The case where we encounter
	// a Terminal
	if((isupper(c[0])))
		strcpy(f[m++],c);
	else
	{
		int i = 0, j = 1;
		for(i = 0; i < count; i++)
		{
		    //printf("ff %d ff",i);
			if(!strcmp(calc_first[i][0],c))

				break;

		}

		//Including the First set of the
		// Non-Terminal in the Follow of
		// the original query
		while(strcmp(calc_first[i][j],"!"))
		{
			if(strcmp(calc_first[i][j],"#"))
			{
			   // printf("4");
			    //printf("ff %d %d %d ff",i,j,m                  );
                strcpy(f[m++],calc_first[i][j]);

                //printf("%s",f[m-1]);
			}
			else
			{
			    //printf("5");
				if(!strcmp(production[c1][c2],""))
				{
					// Case where we reach the
					// end of a production
					//printf("6");
					follow(production[c1][0]);
				}
				else
				{
					// Recursion to the next symbol
					// in case we encounter a "#"
					//printf(" 7 ");
					followfirst(production[c1][c2], c1, c2+1);
				}
			}
			j++;
		}
	}
}

void initializeProductions(){
   int x,y,z;
    production = (char***)malloc(sizeof(char**)*RULECOUNT);
    for(x=0;x<RULECOUNT;x++)
        {
            production[x] = (char**) malloc(sizeof(char*) * COLUMNS);
            for(y=0;y<COLUMNS;y++)
                production[x][y] = (char*) malloc(sizeof(char) * 25);
        }
    production[0][0]=strcpy(production[0][0],"grammar");
    production[0][1]=strcpy(production[0][1],"->");
    production[0][2]=strcpy(production[0][2],"moduleDeclarations");
    production[0][3]=strcpy(production[0][3],"otherModules");
    production[0][4]=strcpy(production[0][4],"driverModule");
    production[0][5]=strcpy(production[0][5],"otherModules");
    strcpy(production[0][6],"");

    production[1][0]=strcpy(production[1][0],"moduleDeclarations");
    production[1][1]=strcpy(production[1][1],"->");
    production[1][2]=strcpy(production[1][2],"moduleDeclaration");
    production[1][3]=strcpy(production[1][3],"moduleDeclarations");
    strcpy(production[1][4],"");

    production[2][0]=strcpy(production[2][0],"moduleDeclarations");
    production[2][1]=strcpy(production[2][1],"->");
    production[2][2]=strcpy(production[2][2],"#");
    strcpy(production[2][3],"");

    production[3][0]=strcpy(production[3][0],"moduleDeclaration");
    production[3][1]=strcpy(production[3][1],"->");
    production[3][2]=strcpy(production[3][2],"DECLARE");
    production[3][3]=strcpy(production[3][3],"MODULE");
    production[3][4]=strcpy(production[3][4],"ID");
    production[3][5]=strcpy(production[3][5],"SEMICOL");
strcpy(production[3][6],"");

    production[4][0]=strcpy(production[4][0],"otherModules");
    production[4][1]=strcpy(production[4][1],"->");
    production[4][2]=strcpy(production[4][2],"module");
    production[4][3]=strcpy(production[4][3],"otherModules");
strcpy(production[4][4],"");

    production[5][0]=strcpy(production[5][0],"otherModules");
    production[5][1]=strcpy(production[5][1],"->");
    production[5][2]=strcpy(production[5][2],"#");
strcpy(production[5][3],"");

    production[6][0]=strcpy(production[6][0],"driverModule");
    production[6][1]=strcpy(production[6][1],"->");
    production[6][2]=strcpy(production[6][2],"DRIVERDEF");
    production[6][3]=strcpy(production[6][3],"DRIVER");
    production[6][4]=strcpy(production[6][4],"PROGRAM");
    production[6][5]=strcpy(production[6][5],"DRIVERENDDEF");

    production[6][6]=strcpy(production[6][6],"moduleDef");
strcpy(production[6][7],"");

    production[7][0]=strcpy(production[7][0],"module");
    production[7][1]=strcpy(production[7][1],"->");
    production[7][2]=strcpy(production[7][2],"DEF");
    production[7][3]=strcpy(production[7][3],"MODULE");
    production[7][4]=strcpy(production[7][4],"ID");
    production[7][5]=strcpy(production[7][5],"ENDDEF");
    production[7][6]=strcpy(production[7][6],"TAKES");
    production[7][7]=strcpy(production[7][7],"INPUT");
    production[7][8]=strcpy(production[7][8],"SQBO");
    production[7][9]=strcpy(production[7][9],"input_plist");
    production[7][10]=strcpy(production[7][10],"SQBC");
    production[7][11]=strcpy(production[7][11],"SEMICOL");
    production[7][12]=strcpy(production[7][12],"ret");
    production[7][13]=strcpy(production[7][13],"moduleDef");
strcpy(production[7][14],"");

    production[8][0]=strcpy(production[8][0],"ret");
    production[8][1]=strcpy(production[8][1],"->");
    production[8][2]=strcpy(production[8][2],"RETURNS");
    production[8][3]=strcpy(production[8][3],"SQBO");
    production[8][4]=strcpy(production[8][4],"output_plist");
    production[8][5]=strcpy(production[8][5],"SQBC");
    production[8][6]=strcpy(production[8][6],"SEMICOL");
strcpy(production[8][7],"");

    production[9][0]=strcpy(production[9][0],"ret");
    production[9][1]=strcpy(production[9][1],"->");
    production[9][2]=strcpy(production[9][2],"#");
strcpy(production[9][3],"");

    production[10][0]=strcpy(production[10][0],"input_plist");
    production[10][1]=strcpy(production[10][1],"->");
    production[10][2]=strcpy(production[10][2],"ID");
    production[10][3]=strcpy(production[10][3],"COLON");
    production[10][4]=strcpy(production[10][4],"dataType");
    production[10][5]=strcpy(production[10][5],"n1");
strcpy(production[10][6],"");

    production[11][0]=strcpy(production[11][0],"n1");
    production[11][1]=strcpy(production[11][1],"->");
    production[11][2]=strcpy(production[11][2],"COMMA");
    production[11][3]=strcpy(production[11][3],"ID");
    production[11][4]=strcpy(production[11][4],"COLON");
    production[11][5]=strcpy(production[11][5],"dataType");
    production[11][6]=strcpy(production[11][6],"n1");
strcpy(production[11][7],"");

    production[12][0]=strcpy(production[12][0],"n1");
    production[12][1]=strcpy(production[12][1],"->");
    production[12][2]=strcpy(production[12][2],"#");
strcpy(production[12][3],"");

    production[13][0]=strcpy(production[13][0],"output_plist");
    production[13][1]=strcpy(production[13][1],"->");
    production[13][2]=strcpy(production[13][2],"ID");
    production[13][3]=strcpy(production[13][3],"COLON");
    production[13][4]=strcpy(production[13][4],"type");
    production[13][5]=strcpy(production[13][5],"n2");
strcpy(production[13][6],"");

    production[14][0]=strcpy(production[14][0],"n2");
    production[14][1]=strcpy(production[14][1],"->");
    production[14][2]=strcpy(production[14][2],"COMMA");
    production[14][3]=strcpy(production[14][3],"ID");
    production[14][4]=strcpy(production[14][4],"COLON");
    production[14][5]=strcpy(production[14][5],"type");
    production[14][6]=strcpy(production[14][6],"n2");
strcpy(production[14][7],"");

    production[15][0]=strcpy(production[15][0],"n2");
    production[15][1]=strcpy(production[15][1],"->");
    production[15][2]=strcpy(production[15][2],"#");
strcpy(production[15][3],"");

    production[16][0]=strcpy(production[16][0],"dataType");
    production[16][1]=strcpy(production[16][1],"->");
    production[16][2]=strcpy(production[16][2],"ARRAY");
    production[16][3]=strcpy(production[16][3],"SQBO");
    production[16][4]=strcpy(production[16][4],"range_arrays");
    production[16][5]=strcpy(production[16][5],"SQBC");
    production[16][6]=strcpy(production[16][6],"OF");
    production[16][7]=strcpy(production[16][7],"type");
strcpy(production[16][8],"");

    production[17][0]=strcpy(production[17][0],"range_arrays");
    production[17][1]=strcpy(production[17][1],"->");
    production[17][2]=strcpy(production[17][2],"index");
    production[17][3]=strcpy(production[17][3],"RANGEOP");
    production[17][4]=strcpy(production[17][4],"index");
strcpy(production[17][5],"");

    production[18][0]=strcpy(production[18][0],"type");
    production[18][1]=strcpy(production[18][1],"->");
    production[18][2]=strcpy(production[18][2],"INTEGER");
strcpy(production[18][3],"");

    production[19][0]=strcpy(production[19][0],"type");
    production[19][1]=strcpy(production[19][1],"->");
    production[19][2]=strcpy(production[19][2],"REAL");
strcpy(production[19][3],"");

    production[20][0]=strcpy(production[20][0],"type");
    production[20][1]=strcpy(production[20][1],"->");
    production[20][2]=strcpy(production[20][2],"BOOLEAN");
strcpy(production[20][3],"");

    production[21][0]=strcpy(production[21][0],"moduleDef");
    production[21][1]=strcpy(production[21][1],"->");
    production[21][2]=strcpy(production[21][2],"START");
    production[21][3]=strcpy(production[21][3],"statements");
    production[21][4]=strcpy(production[21][4],"END");
strcpy(production[21][5],"");

    production[22][0]=strcpy(production[22][0],"statements");
    production[22][1]=strcpy(production[22][1],"->");
    production[22][2]=strcpy(production[22][2],"statement");
    production[22][3]=strcpy(production[22][3],"statements");
strcpy(production[22][4],"");

    production[23][0]=strcpy(production[23][0],"statements");
    production[23][1]=strcpy(production[23][1],"->");
    production[23][2]=strcpy(production[23][2],"#");
strcpy(production[23][3],"");

    production[24][0]=strcpy(production[24][0],"statement");
    production[24][1]=strcpy(production[24][1],"->");
    production[24][2]=strcpy(production[24][2],"ioStmt");
strcpy(production[24][3],"");

    production[25][0]=strcpy(production[25][0],"statement");
    production[25][1]=strcpy(production[25][1],"->");
    production[25][2]=strcpy(production[25][2],"simpleStmt");
strcpy(production[25][3],"");

    production[26][0]=strcpy(production[26][0],"statement");
    production[26][1]=strcpy(production[26][1],"->");
    production[26][2]=strcpy(production[26][2],"declareStmt");
strcpy(production[26][3],"");

    production[27][0]=strcpy(production[27][0],"statement");
    production[27][1]=strcpy(production[27][1],"->");
    production[27][2]=strcpy(production[27][2],"conditionalStmt");
strcpy(production[27][3],"");

    production[28][0]=strcpy(production[28][0],"statement");
    production[28][1]=strcpy(production[28][1],"->");
    production[28][2]=strcpy(production[28][2],"iterativeStmt");
strcpy(production[28][3],"");

    production[29][0]=strcpy(production[29][0],"ioStmt");
    production[29][1]=strcpy(production[29][1],"->");
    production[29][2]=strcpy(production[29][2],"GET_VALUE");
    production[29][3]=strcpy(production[29][3],"BO");
    production[29][4]=strcpy(production[29][4],"ID");
    production[29][5]=strcpy(production[29][5],"BC");
    production[29][6]=strcpy(production[29][6],"SEMICOL");
strcpy(production[29][7],"");

    production[30][0]=strcpy(production[30][0],"ioStmt");
    production[30][1]=strcpy(production[30][1],"->");
    production[30][2]=strcpy(production[30][2],"PRINT");
    production[30][3]=strcpy(production[30][3],"BO");
    production[30][4]=strcpy(production[30][4],"var");
    production[30][5]=strcpy(production[30][5],"BC");
    production[30][6]=strcpy(production[30][6],"SEMICOL");
strcpy(production[30][7],"");

    production[31][0]=strcpy(production[31][0],"boolConstt");
    production[31][1]=strcpy(production[31][1],"->");
    production[31][2]=strcpy(production[31][2],"TRUE");
strcpy(production[31][3],"");

    production[32][0]=strcpy(production[32][0],"boolConstt");
    production[32][1]=strcpy(production[32][1],"->");
    production[32][2]=strcpy(production[32][2],"FALSE");
strcpy(production[32][3],"");

    production[33][0]=strcpy(production[33][0],"var_id_num");
    production[33][1]=strcpy(production[33][1],"->");
    production[33][2]=strcpy(production[33][2],"ID");
    production[33][3]=strcpy(production[33][3],"whichId");
strcpy(production[33][4],"");

    production[34][0]=strcpy(production[34][0],"var_id_num");
    production[34][1]=strcpy(production[34][1],"->");
    production[34][2]=strcpy(production[34][2],"NUM");
strcpy(production[34][3],"");

    production[35][0]=strcpy(production[35][0],"var_id_num");
    production[35][1]=strcpy(production[35][1],"->");
    production[35][2]=strcpy(production[35][2],"RNUM");
strcpy(production[35][3],"");

    production[36][0]=strcpy(production[36][0],"var");
    production[36][1]=strcpy(production[36][1],"->");
    production[36][2]=strcpy(production[36][2],"var_id_num");
strcpy(production[36][3],"");

    production[37][0]=strcpy(production[37][0],"var");
    production[37][1]=strcpy(production[37][1],"->");
    production[37][2]=strcpy(production[37][2],"boolConstt");
strcpy(production[37][3],"");

    production[38][0]=strcpy(production[38][0],"whichId");
    production[38][1]=strcpy(production[38][1],"->");
    production[38][2]=strcpy(production[38][2],"SQBO");
    production[38][3]=strcpy(production[38][3],"index");
    production[38][4]=strcpy(production[38][4],"SQBC");
strcpy(production[38][5],"");

    production[39][0]=strcpy(production[39][0],"whichId");
    production[39][1]=strcpy(production[39][1],"->");
    production[39][2]=strcpy(production[39][2],"#");
strcpy(production[39][3],"");

    production[40][0]=strcpy(production[40][0],"simpleStmt");
    production[40][1]=strcpy(production[40][1],"->");
    production[40][2]=strcpy(production[40][2],"assignmentStmt");
strcpy(production[40][3],"");

    production[41][0]=strcpy(production[41][0],"simpleStmt");
    production[41][1]=strcpy(production[41][1],"->");
    production[41][2]=strcpy(production[41][2],"moduleReuseStmt");
strcpy(production[41][3],"");

    production[42][0]=strcpy(production[42][0],"assignmentStmt");
    production[42][1]=strcpy(production[42][1],"->");
    production[42][2]=strcpy(production[42][2],"ID");
    production[42][3]=strcpy(production[42][3],"whichStmt");
strcpy(production[42][4],"");

    production[43][0]=strcpy(production[43][0],"whichStmt");
    production[43][1]=strcpy(production[43][1],"->");
    production[43][2]=strcpy(production[43][2],"lvalueIDStmt");
strcpy(production[43][3],"");

    production[44][0]=strcpy(production[44][0],"whichStmt");
    production[44][1]=strcpy(production[44][1],"->");
    production[44][2]=strcpy(production[44][2],"lvalueARRStmt");
strcpy(production[44][3],"");

    production[45][0]=strcpy(production[45][0],"lvalueIDStmt");
    production[45][1]=strcpy(production[45][1],"->");
    production[45][2]=strcpy(production[45][2],"ASSIGNOP");
    production[45][3]=strcpy(production[45][3],"expression");
    production[45][4]=strcpy(production[45][4],"SEMICOL");
strcpy(production[45][5],"");

    production[46][0]=strcpy(production[46][0],"lvalueARRStmt");
    production[46][1]=strcpy(production[46][1],"->");
    production[46][2]=strcpy(production[46][2],"SQBO");
    production[46][3]=strcpy(production[46][3],"index");
    production[46][4]=strcpy(production[46][4],"SQBC");
    production[46][5]=strcpy(production[46][5],"ASSIGNOP");
    production[46][6]=strcpy(production[46][6],"expression");
    production[46][7]=strcpy(production[46][7],"SEMICOL");
strcpy(production[46][8],"");

    production[47][0]=strcpy(production[47][0],"index");
    production[47][1]=strcpy(production[47][1],"->");
    production[47][2]=strcpy(production[47][2],"NUM");
strcpy(production[47][3],"");

    production[48][0]=strcpy(production[48][0],"index");
    production[48][1]=strcpy(production[48][1],"->");
    production[48][2]=strcpy(production[48][2],"ID");
strcpy(production[48][3],"");

    production[49][0]=strcpy(production[49][0],"moduleReuseStmt");
    production[49][1]=strcpy(production[49][1],"->");
    production[49][2]=strcpy(production[49][2],"optional");
    production[49][3]=strcpy(production[49][3],"USE");
    production[49][4]=strcpy(production[49][4],"MODULE");
    production[49][5]=strcpy(production[49][5],"ID");
    production[49][6]=strcpy(production[49][6],"WITH");
    production[49][7]=strcpy(production[49][7],"PARAMETERS");
    production[49][8]=strcpy(production[49][8],"idList");
    production[49][9]=strcpy(production[49][9],"SEMICOL");
strcpy(production[49][10],"");

    production[50][0] = strcpy(production[50][0],"optional");
    production[50][1] = strcpy(production[50][1],"->");
    production[50][2] = strcpy(production[50][2],"SQBO");
    production[50][3] = strcpy(production[50][3],"idList");
    production[50][4] = strcpy(production[50][4],"SQBC");
    production[50][5] = strcpy(production[50][5],"ASSIGNOP");
strcpy(production[50][6],"");

    production[51][0] = strcpy(production[51][0],"optional");
    production[51][1] = strcpy(production[51][1],"->");
    production[51][2] = strcpy(production[51][2],"#");
strcpy(production[51][3],"");

    production[52][0] = strcpy(production[52][0],"idList");
    production[52][1] = strcpy(production[52][1],"->");
    production[52][2] = strcpy(production[52][2],"ID");
    production[52][3] = strcpy(production[52][3],"n3");
strcpy(production[52][4],"");

    production[53][0] = strcpy(production[53][0],"n3");
    production[53][1] = strcpy(production[53][1],"->");
    production[53][2] = strcpy(production[53][2],"COMMA");
    production[53][3] = strcpy(production[53][3],"ID");
    production[53][4] = strcpy(production[53][4],"n3");
strcpy(production[53][5],"");

    production[54][0] = strcpy(production[54][0],"n3");
    production[54][1] = strcpy(production[54][1],"->");
    production[54][2] = strcpy(production[54][2],"#");
    strcpy(production[54][3],"");

    production[55][0]=strcpy(production[55][0],"expression");
    production[55][1]=strcpy(production[55][1],"->");
    production[55][2]=strcpy(production[55][2],"arithmeticOrBooleanExpr");
strcpy(production[55][3],"");

    production[56][0]=strcpy(production[56][0],"expression");
    production[56][1]=strcpy(production[56][1],"->");
    production[56][2]=strcpy(production[56][2],"u");
strcpy(production[56][3],"");

    production[57][0]=strcpy(production[57][0],"u");
    production[57][1]=strcpy(production[57][1],"->");
    production[57][2]=strcpy(production[57][2],"unary_op");
    production[57][3]=strcpy(production[57][3],"new_NT");
strcpy(production[57][4],"");

    production[58][0]=strcpy(production[58][0],"new_NT");
    production[58][1]=strcpy(production[58][1],"->");
    production[58][2]=strcpy(production[58][2],"BO");
    production[58][3]=strcpy(production[58][3],"arithmeticExpr");
    production[58][4]=strcpy(production[58][4],"BC");
strcpy(production[58][5],"");

    production[59][0]=strcpy(production[59][0],"new_NT");
    production[59][1]=strcpy(production[59][1],"->");
    production[59][2]=strcpy(production[59][2],"var_id_num");
strcpy(production[59][3],"");

    production[60][0]=strcpy(production[60][0],"unary_op");
    production[60][1]=strcpy(production[60][1],"->");
    production[60][2]=strcpy(production[60][2],"PLUS");
strcpy(production[60][3],"");

    production[61][0]=strcpy(production[61][0],"unary_op");
    production[61][1]=strcpy(production[61][1],"->");
    production[61][2]=strcpy(production[61][2],"MINUS");
strcpy(production[61][3],"");

    production[62][0]=strcpy(production[62][0],"arithmeticOrBooleanExpr");
    production[62][1]=strcpy(production[62][1],"->");
    production[62][2]=strcpy(production[62][2],"anyTerm");
    production[62][3]=strcpy(production[62][3],"n7");
strcpy(production[62][4],"");

    production[63][0]=strcpy(production[63][0],"n7");
    production[63][1]=strcpy(production[63][1],"->");
    production[63][2]=strcpy(production[63][2],"logicalOp");
    production[63][3]=strcpy(production[63][3],"anyTerm");
    production[63][4]=strcpy(production[63][4],"n7");
strcpy(production[63][5],"");

    production[64][0]=strcpy(production[64][0],"n7");
    production[64][1]=strcpy(production[64][1],"->");
    production[64][2]=strcpy(production[64][2],"#");
strcpy(production[64][3],"");

    production[65][0]=strcpy(production[65][0],"anyTerm");
    production[65][1]=strcpy(production[65][1],"->");
    production[65][2]=strcpy(production[65][2],"arithmeticExpr");
    production[65][3]=strcpy(production[65][3],"n8");
strcpy(production[65][4],"");

    production[66][0]=strcpy(production[66][0],"anyTerm");
    production[66][1]=strcpy(production[66][1],"->");
    production[66][2]=strcpy(production[66][2],"boolConstt");
strcpy(production[66][3],"");

    production[67][0]=strcpy(production[67][0],"n8");
    production[67][1]=strcpy(production[67][1],"->");
    production[67][2]=strcpy(production[67][2],"relationalOp");
    production[67][3]=strcpy(production[67][3],"arithmeticExpr");
strcpy(production[67][4],"");

    production[68][0]=strcpy(production[68][0],"n8");
    production[68][1]=strcpy(production[68][1],"->");
    production[68][2]=strcpy(production[68][2],"#");
strcpy(production[68][3],"");

    production[69][0] = strcpy(production[69][0],"arithmeticExpr");
    production[69][1] = strcpy(production[69][1],"->");
    production[69][2] = strcpy(production[69][2],"term");
    production[69][3] = strcpy(production[69][3],"n4");
strcpy(production[69][4],"");

    production[70][0] = strcpy(production[70][0],"n4");
    production[70][1] = strcpy(production[70][1],"->");
    production[70][2] = strcpy(production[70][2],"op1");
    production[70][3] = strcpy(production[70][3],"term");
    production[70][4] = strcpy(production[70][4],"n4");
strcpy(production[70][5],"");

    production[71][0] = strcpy(production[71][0],"n4");
    production[71][1] = strcpy(production[71][1],"->");
    production[71][2] = strcpy(production[71][2],"#");
strcpy(production[71][3],"");



    production[72][0] = strcpy(production[72][0],"term");
    production[72][1] = strcpy(production[72][1],"->");
    production[72][2] = strcpy(production[72][2],"factor");
    production[72][3] = strcpy(production[72][3],"n5");
strcpy(production[72][4],"");

    production[73][0] = strcpy(production[73][0],"n5");
    production[73][1] = strcpy(production[73][1],"->");
    production[73][2] = strcpy(production[73][2],"op2");
    production[73][3] = strcpy(production[73][3],"factor");
    production[73][4] = strcpy(production[73][4],"n5");
strcpy(production[73][5],"");

    production[74][0] = strcpy(production[74][0],"n5");
    production[74][1] = strcpy(production[74][1],"->");
    production[74][2] = strcpy(production[74][2],"#");
strcpy(production[74][3],"");

    production[75][0] = strcpy(production[75][0],"factor");
    production[75][1] = strcpy(production[75][1],"->");
    production[75][2] = strcpy(production[75][2],"BO");
    production[75][3] = strcpy(production[75][3],"arithmeticOrBooleanExpr");
    production[75][4] = strcpy(production[75][4],"BC");
strcpy(production[75][5],"");

    production[76][0] = strcpy(production[76][0],"factor");
    production[76][1] = strcpy(production[76][1],"->");
    production[76][2] = strcpy(production[76][2],"var_id_num");
strcpy(production[76][3],"");

    production[77][0] = strcpy(production[77][0],"op1");
    production[77][1] = strcpy(production[77][1],"->");
    production[77][2] = strcpy(production[77][2],"PLUS");
    strcpy(production[77][3],"");

    production[78][0] = strcpy(production[78][0],"op1");
    production[78][1] = strcpy(production[78][1],"->");
    production[78][2] = strcpy(production[78][2],"MINUS");
    strcpy(production[78][3],"");

    production[79][0] = strcpy(production[79][0],"op2");
    production[79][1] = strcpy(production[79][1],"->");
    production[79][2] = strcpy(production[79][2],"MUL");
    strcpy(production[79][3],"");

    production[80][0] = strcpy(production[80][0],"op2");
    production[80][1] = strcpy(production[80][1],"->");
    production[80][2] = strcpy(production[80][2],"DIV");
    strcpy(production[80][3],"");

    production[81][0] = strcpy(production[81][0],"logicalOp");
    production[81][1] = strcpy(production[81][1],"->");
    production[81][2] = strcpy(production[81][2],"AND");
    strcpy(production[81][3],"");

    production[82][0] = strcpy(production[82][0],"logicalOp");
    production[82][1] = strcpy(production[82][1],"->");
    production[82][2] = strcpy(production[82][2],"OR");
    strcpy(production[82][3],"");

    production[83][0] = strcpy(production[83][0],"relationalOp");
    production[83][1] = strcpy(production[83][1],"->");
    production[83][2] = strcpy(production[83][2],"LT");
    strcpy(production[83][3],"");

    production[84][0] = strcpy(production[84][0],"relationalOp");
    production[84][1] = strcpy(production[84][1],"->");
    production[84][2] = strcpy(production[84][2],"LE");
    strcpy(production[84][3],"");

    production[85][0] = strcpy(production[85][0],"relationalOp");
    production[85][1] = strcpy(production[85][1],"->");
    production[85][2] = strcpy(production[85][2],"GT");
    strcpy(production[85][3],"");

    production[86][0] = strcpy(production[86][0],"relationalOp");
    production[86][1] = strcpy(production[86][1],"->");
    production[86][2] = strcpy(production[86][2],"GE");
    strcpy(production[86][3],"");

    production[87][0] = strcpy(production[87][0],"relationalOp");
    production[87][1] = strcpy(production[87][1],"->");
    production[87][2] = strcpy(production[87][2],"EQ");
    strcpy(production[87][3],"");

    production[88][0] = strcpy(production[88][0],"relationalOp");
    production[88][1] = strcpy(production[88][1],"->");
    production[88][2] = strcpy(production[88][2],"NE");
    strcpy(production[88][3],"");

    production[89][0] = strcpy(production[89][0],"declareStmt");
    production[89][1] = strcpy(production[89][1],"->");
    production[89][2] = strcpy(production[89][2],"DECLARE");
    production[89][3] = strcpy(production[89][3],"idList");
    production[89][4] = strcpy(production[89][4],"COLON");
    production[89][5] = strcpy(production[89][5],"dataType");
    production[89][6] = strcpy(production[89][6],"SEMICOL");
    strcpy(production[89][7],"");

    production[90][0] = strcpy(production[90][0],"conditionalStmt");
    production[90][1] = strcpy(production[90][1],"->");
    production[90][2] = strcpy(production[90][2],"SWITCH");
    production[90][3] = strcpy(production[90][3],"BO");
    production[90][4] = strcpy(production[90][4],"ID");
    production[90][5] = strcpy(production[90][5],"BC");
    production[90][6] = strcpy(production[90][6],"START");
    production[90][7] = strcpy(production[90][7],"caseStmts");
    production[90][8] = strcpy(production[90][8],"default");
    production[90][9] = strcpy(production[90][9],"END");
    strcpy(production[90][10],"");

    production[91][0] = strcpy(production[91][0],"caseStmts");
    production[91][1] = strcpy(production[91][1],"->");
    production[91][2] = strcpy(production[91][2],"CASE");
    production[91][3] = strcpy(production[91][3],"value");
    production[91][4] = strcpy(production[91][4],"COLON");
    production[91][5] = strcpy(production[91][5],"statements");
    production[91][6] = strcpy(production[91][6],"BREAK");
    production[91][7] = strcpy(production[91][7],"SEMICOL");
    production[91][8] = strcpy(production[91][8],"n9");
    strcpy(production[91][9],"");

    production[92][0] = strcpy(production[92][0],"n9");
    production[92][1] = strcpy(production[92][1],"->");
    production[92][2] = strcpy(production[92][2],"CASE");
    production[92][3] = strcpy(production[92][3],"value");
    production[92][4] = strcpy(production[92][4],"COLON");
    production[92][5] = strcpy(production[92][5],"statements");
    production[92][6] = strcpy(production[92][6],"BREAK");
    production[92][7] = strcpy(production[92][7],"SEMICOL");
    production[92][8] = strcpy(production[92][8],"n9");
    strcpy(production[92][9],"");

    production[93][0] = strcpy(production[93][0],"n9");
    production[93][1] = strcpy(production[93][1],"->");
    production[93][2] = strcpy(production[93][2],"#");
    strcpy(production[93][3],"");

    production[94][0] = strcpy(production[94][0],"value");
    production[94][1] = strcpy(production[94][1],"->");
    production[94][2] = strcpy(production[94][2],"NUM");
    strcpy(production[94][3],"");

    production[95][0] = strcpy(production[95][0],"value");
    production[95][1] = strcpy(production[95][1],"->");
    production[95][2] = strcpy(production[95][2],"TRUE");
    strcpy(production[95][3],"");

    production[96][0] = strcpy(production[96][0],"value");
    production[96][1] = strcpy(production[96][1],"->");
    production[96][2] = strcpy(production[96][2],"FALSE");
    strcpy(production[96][3],"");

    production[97][0] = strcpy(production[97][0],"default");
    production[97][1] = strcpy(production[97][1],"->");
    production[97][2] = strcpy(production[97][2],"DEFAULT");
    production[97][3] = strcpy(production[97][3],"COLON");
    production[97][4] = strcpy(production[97][4],"statements");
    production[97][5] = strcpy(production[97][5],"BREAK");
    production[97][6] = strcpy(production[97][6],"SEMICOL");
    strcpy(production[97][7],"");

    production[98][0] = strcpy(production[98][0],"default");
    production[98][1] = strcpy(production[98][1],"->");
    production[98][2] = strcpy(production[98][2],"#");
    strcpy(production[98][3],"");

    production[99][0] = strcpy(production[99][0],"iterativeStmt");
    production[99][1] = strcpy(production[99][1],"->");
    production[99][2] = strcpy(production[99][2],"FOR");
    production[99][3] = strcpy(production[99][3],"BO");
    production[99][4] = strcpy(production[99][4],"ID");
    production[99][5] = strcpy(production[99][5],"IN");
    production[99][6] = strcpy(production[99][6],"range");
    production[99][7] = strcpy(production[99][7],"BC");
    production[99][8] = strcpy(production[99][8],"START");
    production[99][9] = strcpy(production[99][9],"statements");
    production[99][10] = strcpy(production[99][10],"END");
    strcpy(production[99][11],"");

    production[100][0] = strcpy(production[100][0],"iterativeStmt");
    production[100][1] = strcpy(production[100][1],"->");
    production[100][2] = strcpy(production[100][2],"WHILE");
    production[100][3] = strcpy(production[100][3],"BO");
    production[100][4] = strcpy(production[100][4],"arithmeticOrBooleanExpr");
    production[100][5] = strcpy(production[100][5],"BC");
    production[100][6] = strcpy(production[100][6],"START");
    production[100][7] = strcpy(production[100][7],"statements");
    production[100][8] = strcpy(production[100][8],"END");
    strcpy(production[100][9],"");

    production[101][0] = strcpy(production[101][0],"range");
    production[101][1] = strcpy(production[101][1],"->");
    production[101][2] = strcpy(production[101][2],"NUM");
    production[101][3] = strcpy(production[101][3],"RANGEOP");
    production[101][4] = strcpy(production[101][4],"NUM");
    strcpy(production[101][5],"");

    production[102][0]=strcpy(production[102][0],"dataType");
    production[102][1]=strcpy(production[102][1],"->");
    production[102][2]=strcpy(production[102][2],"INTEGER");
    strcpy(production[102][3],"");

    production[103][0]=strcpy(production[103][0],"dataType");
    production[103][1]=strcpy(production[103][1],"->");
    production[103][2]=strcpy(production[103][2],"REAL");
    strcpy(production[103][3],"");

    production[104][0]=strcpy(production[104][0],"dataType");
    production[104][1]=strcpy(production[104][1],"->");
    production[104][2]=strcpy(production[104][2],"BOOLEAN");
    strcpy(production[104][3],"");


    /* int i=0,j=0;
    for(;i<RULECOUNT;i++)
    {
        while(1)
        {
            if(strcmp(production[i][j],""))
            {
                j++;

            }
            else
                break;
        }
        j++;
        for(;j<COLUMNS;j++)
        {
            production[i][j]=NULL;
        }
    }*/
}




 void computeFirstAndFollowSets()
    {
        int e,x,y;
        for(x=0;x<NTCOUNT;++x){
            for(y=0;y<NTCOLS;++y){
                calc_first[x][y] = (char*)malloc(25);
                calc_follow[x][y] = (char*) malloc(25);
            }
        }
        for(x=0;x<NTCOL;x++)
        {
            first[x] = (char*) malloc(sizeof(char)*25);
            f[x] = (char*) malloc(sizeof(char)*25);
        }
        char *ck = (char*) malloc(sizeof(char)*25);
        int jm = 0;

        int i,k;
        char *c = malloc(sizeof(char)*25);

        int kay;
        char *done[count];
        for (x=0;x<count;x++)
            done[x] = (char*) malloc(25);
        int ptr = -1;

        // Initializing the calc_first array
        for(k = 0; k < NTCOUNT; k++) {
            for(kay = 0; kay < NTCOLS; kay++) {
                strcpy(calc_first[k][kay],"!");
            }
        }
        int point1 = 0, point2, xxx;

        for(k = 0; k < count; k++)
        {
            strcpy(c,  production[k][0]);
            point2 = 0;
            xxx = 0;

            // Checking if First of c has
            // already been calculated
            for(kay = 0; kay <= ptr; kay++)
                if(!strcmp(c ,done[kay]))
                    xxx = 1;

            if (xxx == 1)
                continue;

            // Function call
            findfirst(c, 0, 0);
            ptr += 1;

            // Adding c to the calculated list
            strcpy(done[ptr], c);
          //  printf("\n First(%s) = { ", c);
            strcpy(calc_first[point1][point2++],c);

            // Printing the First Sets of the grammar
            for(i = 0 + jm; i < n; i++) {
                int lark = 0, chk = 0;

                for(lark = 0; lark < point2; lark++) {

                    if (!strcmp(first[i],calc_first[point1][lark]))
                    {
                        chk = 1;
                        break;
                    }
                }
                if(chk == 0)               {
                   // printf("%s, ", first[i]);
                    strcpy(calc_first[point1][point2++], first[i]);
                }
            }
            //printf("}\n");
            jm = n;
            point1++;
        }
        //printf("\n");
        //printf("-----------------------------------------------\n\n");
        char *donee[count];
        for(x = 0;x<count;x++){
            donee[x] = (char*)malloc(25);
        }
        ptr = -1;

        // Initializing the calc_follow array
        for(k = 0; k < NTCOUNT; k++) {
            for(kay = 0; kay < NTCOLS; kay++) {
                strcpy(calc_follow[k][kay],"!");
            }
        }
        point1 = 0;
        int land = 0;
        for(e = 0; e < count; e++)
        {
            strcpy(ck,production[e][0]);
            point2 = 0;
            xxx = 0;

            // Checking if Follow of ck
            // has alredy been calculated
            for(kay = 0; kay <= ptr; kay++)
                if(!strcmp(ck, donee[kay]))
                    xxx = 1;

            if (xxx == 1)
                continue;
            land += 1;

            // Function call
            follow(ck);
            //printf("%s",ck);
            ptr += 1;

            // Adding ck to the calculated list
            strcpy(donee[ptr], ck);
           // printf(" Follow(%s) = { ", ck);
            strcpy(calc_follow[point1][point2++],ck);

            // Printing the Follow Sets of the grammar
            for(i = 0 ; i < m; i++) {
                int lark = 0, chk = 0;
                for(lark = 0; lark < point2; lark++)
                {
                    if (!strcmp(f[i],calc_follow[point1][lark]))
                    {
                        chk = 1;
                        break;
                    }
                }
                if(chk == 0)
                {
                 //   printf("%s, ", f[i]);
                    strcpy(calc_follow[point1][point2++],f[i]);
                }
            }
           // printf(" }\n\n");
            m = 0;
            point1++;
        }
    }
/* void printFirstAndFollowSets(){
 int x = 0;
 int y=0;


    while(1){

        if(strcmp(calc_first[x][y],"!")){
            if(y == 0)
                printf("First(%s) ->\t",calc_first[x][y++]);
            else
                printf("%s ",calc_first[x][y++]);
            }
        else{
            x++;
            y=0;
            printf("\n");
            if(x==NTCOUNT||!strcmp(calc_first[x][y],"!")){

                break;
                }
        }
    }
    printf("\n");
    x=0;
    y=0;
    while(1){

        if(strcmp(calc_follow[x][y],"!")){
            if(y == 0)
                printf("Follow(%s) ->\t",calc_follow[x][y++]);
            else
                printf("%s ",calc_follow[x][y++]);
            }
        else{
            x++;
            y=0;
            printf("\n");
            if(x==NTCOUNT||!strcmp(calc_follow[x][y],"!")){
                printf("\n\n\t\t\t\t==========================END==========================\n");
                break;
            }
        }
    }
}  */


char*** getGrammar(){
return production;}
void printGrammar(char ***grammar){
int x,y;
for(x=0;x<RULECOUNT;x++){
        for(y=0;y<COLUMNS;y++)
            printf("%s ",grammar[x][y]);
        printf("\n");
    }
}



void printFirstAndFollowSets()
{
	int x = 0;
	int y=0;
	FILE *fp=fopen("FirstSet.txt","w");	
	while(1)
	{
	        if(strcmp(calc_first[x][y],"!"))
		{
			if(y == 0)
			{
		                fprintf(fp,"First(%s) ->\t",calc_first[x][y]);
		                printf("First(%s) ->\t",calc_first[x][y]);
				y++;
			}            
			else
			{
		                fprintf(fp,"%s ",calc_first[x][y]);
		                printf("%s ",calc_first[x][y]);
				y++;
			}         
		}
	        else
		{
			x++;
			y=0;
			fprintf(fp,"\n");
			printf("\n");
			if(x==NTCOUNT||!strcmp(calc_first[x][y],"!"))
			{
                		break;	
                	}
        	}
	}	
	fprintf(fp,"\n\n\n\n");
	printf("\n\n\n\n");
	x=0;
	y=0;
	while(1)
	{
		if(strcmp(calc_follow[x][y],"!"))
		{
			if(y == 0)
			{
				//fprintf(fp,"Follow(%s) ->\t",calc_follow[x][y]);
	        	        printf("Follow(%s) ->\t",calc_follow[x][y]);
				y++;		
			}
			else
			{
	        	      //  fprintf(fp,"%s ",calc_follow[x][y]);
	        	        printf("%s ",calc_follow[x][y]);
				y++;
			}
		}		
		else
		{
			x++;
			y=0;
			//fprintf(fp,"\n");
			printf("\n");
			if(x==NTCOUNT||!strcmp(calc_follow[x][y],"!"))
			{
				//fprintf(fp,"\n\n\t\t\t\t==========================END==========================\n");
				printf("\n\n\t\t\t\t==========================END==========================\n");
		                break;
			}
		}
	} 
} 






