#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edit_distance.h"
#define MAX_LENGTH (50)

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/
*/
//start
int min(int num1,int num2, int num3)
{
	if(num1 < num2 && num1 < num3)
	{
		return num1;
	}
	else if(num2 < num3)
	{
		return num2;
	}
	else
	{
		return num3;
	}
}



int filesize(char* filename) //gives the number of names in a file
{
    FILE* fptr = fopen(filename, "r");
    int linecounter = 1;
    char c;
    c = getc(fptr);
    while(c != EOF)
    {
        if(c =='\n')
        {
            linecounter++;
        }
        c = getc(fptr);
    }
    fclose(fptr);
    return linecounter;
}

int edit_distance(char * first_string, char * second_string, int print_table){
	int row = strlen(first_string)+1;
	int col = strlen(second_string)+1;
	int pval = print_table;
	int arr[row][col];
	//populate first row and colums with their index values
	int i,j,k,m,n;
	for(j=0;j < col; j++)
	{
		arr[0][j] = j;
	}
	for(i=0; i < row;i++)
	{
		arr[i][0] = i;
	}
	//populate all spots of 2D arr using edit distance formula
	for(i=1;i<row;i++)
	{
		char r_char, c_char;
		r_char = first_string[i-1]; // get each letter of first_string
		for(j=1;j<col;j++)
		{
			c_char = second_string[j-1]; // get each letter of second_string
			if(r_char == c_char)
			{
				arr[i][j]= min(arr[i-1][j]+1, arr[i][j-1]+1, arr[i-1][j-1]);//edit distance formula
			}
			else
			{
				arr[i][j]= min(arr[i-1][j]+1,arr[i][j-1]+1,arr[i-1][j-1]+1);
			}
		}
	}

	//print the 2D arr in given format
	if(pval==1)
	{
		for(m=0;m<row;m++)
		{
			if(m==0)
			{
				printf("   |   |");
				for(k = 0; k<col-1; k++)
				{
					printf("  %c|",second_string[k]);
				}
			}
			printf("\n");
			for(int a=0;a<(k*4)+8;a++)
			{
				printf("-");
			}
			printf("\n");
			if(m>0)
			{
				printf("  %c|",first_string[m-1]);
			}

			for(n=0;n<col;n++)
			{
				if(arr[m][n] < 10)
				{
					if(m==0 && n == 0)
					{
						printf("   |  %d|",arr[m][n]);
					}
					else
					{
						printf("  %d|",arr[m][n]);
					}	
				}
				else
				{
					if(m==0 && n == 0)
					{
						printf("   | %d|",arr[m][n]);
					}
					else
					{
						printf(" %d|",arr[m][n]);
					}
				}
			}
		}  
	}
	return arr[row-1][col-1];
}
	
	  
	  
void spellcheck(char * dictname, char * testname){
		// put all dictionary words into dict array 
	FILE* fp = NULL;
	FILE* fp1 = NULL;
	int result_arr[10];
	int size;
	int e_distance;
	int testsize;
	int i = 0;
	int j = 0;
	int m,n;
	printf("\n\nLoading the dictionary file: %s",dictname);
	printf("\nLoading the test file: %s\n",testname);
	fp = fopen(dictname,"r");
	size = filesize(dictname);
		//printf("dictsize: %d\n",size);
	char dict[size][MAX_LENGTH];
	char min_distance_arr[MAX_LENGTH][MAX_LENGTH];
	while(fscanf(fp, "%s", dict[i]) != EOF)
	{
		i++;
	}
		// put all test words into test array
	fp1 = fopen(testname,"r");
	testsize = filesize(testname);
	//printf("testsize: %d\n",testsize);
	char test[testsize][MAX_LENGTH];
	while(fscanf(fp1, "%s", test[j]) != EOF)
	{
		j++;
	}
	fclose(fp);
	fclose(fp1);
	/*for(i=0; i< testsize; i++)
	{
		printf("%d: %s\n",i, test[i]);
	}*/
		// put all edit_distance values for each word in min_distance_arr 
	for(i=1;i<testsize;i++)
	{
		int min_val = 100;
		n=0;
		printf("\n\n------- Current test word: %s",test[i]);
		  //  get min_val of the min_distance arr
		for(j=1;j<size;j++)
		{
			e_distance = edit_distance(test[i], dict[j],0);
			if(e_distance < min_val)
			{
				min_val = e_distance;
			}
		}
			// if min_val is found, copy the word
		for(m=1;m<size;m++)
		{
			e_distance = edit_distance(test[i], dict[m],0);
			if(min_val == e_distance)
			{
				strcpy(min_distance_arr[n],dict[m]);
				n++;
			}
		}
		printf("\nMinimum distance: %d\n",min_val);
		printf("Words that give minimum distance: \n");
		for(int a =0; a < n; a++)
		{
			printf("%s\n",min_distance_arr[a]);
		}
		
	}
}
