#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#define MAX_MATCHES 1

void time_complexity_calculator(char*, size_t, FILE *);
void memory_complexity_calculator(char*, size_t, FILE *);
int match(const char , const char );
char* remove_white_spaces(char* );

int main(int argc, char const *argv[])
{
    clock_t t;
    t = clock();
    double time_taken;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    

	fp = fopen(argv[1], "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
    
    time_complexity_calculator(line, len, fp);
    //BigO analysis time taken
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\n\ntime_complexity_calculator() took %f seconds to execute \n\n", time_taken);

    fp = fopen(argv[1], "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

    memory_complexity_calculator(line, len, fp);

    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\n\nmemory_complexity_calculator() took %f seconds to execute \n\n", time_taken);
}

void time_complexity_calculator(char* line, size_t len, FILE * fp){

    ssize_t read;
    int level = 0;
	int line_number = 0;
    int closing_statement = 0;
    int loop_statements = 0;
    int const_statements = 0 ;


    printf("**************************************************\n");
    while ((read = getline(&line, &len, fp)) != -1) {
       
		line_number++;
		if (strstr(line, "for") || strstr(line, "while")){
            level++;
            printf("Line %d: %s", line_number, line); 
			printf("\tloop() LEVEL %d n^%d\n\n", level, level);
			
		}

        else if (strstr(line, "if") || strstr(line, "else if") || strstr(line, "else")){
            const_statements++;
            printf("Line %d: %s", line_number, line); 
			printf("\tConstant time statements %dn \n\n", const_statements);
            continue;
			
		}
		else if (strstr(line, "}")) { 
            closing_statement++;
            if (closing_statement == level) {
                loop_statements = level;
                level = 0;
                closing_statement = 0;
                printf("Line %d : Level Closing.\n\n", line_number);
                printf("**************************************************\n");
            }
            if (closing_statement > level) {
                break;
            }
		}
		
    }

    printf("Time Complexity O(n) = O(n^%d + %dn) ==> O(n^%d) \n", loop_statements, const_statements, loop_statements);

    fclose(fp);
    if (line)
        free(line);
    
}

int match(const char *string, const char *pattern)
{
    regex_t re;

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) return 0;

    int status = regexec(&re, string, 0, NULL, 0);
    regfree(&re);

    if (status != 0) return 0;
    return 1;
}

char* remove_white_spaces(char* str){
    static char str1[99];
    int count = 0, j, k;
  
    while (str[count] == ' ') {
        count++;
    }
  
    for (j = count, k = 0; str[j] != '\0'; j++, k++) {
        str1[k] = str[j];
    }
    str1[k] = '\0';
  
    return str1;
}

void memory_complexity_calculator(char* line, size_t len, FILE * fp){

    ssize_t read;
    int level = 0;
	int line_number = 0;
    int sum_of_space_size = 0;


    const char * re = "int|char|float|double|long";

    printf("**************************************************\n");
    while ((read = getline(&line, &len, fp)) != -1) {

        line_number++;
        //printf("Exact match ! %s", line);
		if ( match(line, re)) {
            if (strncmp(remove_white_spaces(line), "int", 3) == 0) {
                sum_of_space_size +=4;
                printf("\nLine %d: %s -> 4 Byte", line_number, remove_white_spaces(line));
                 
            }

            if (strncmp(remove_white_spaces(line), "char", 4) == 0) {
                sum_of_space_size +=sizeof(line);
                printf("\nLine %d: %s -> 1 Byte per character", line_number, remove_white_spaces(line));
                
            }

            if (strncmp(remove_white_spaces(line), "float", 5) == 0) {
                sum_of_space_size +=sizeof(float);
                printf("\nLine %d: %s -> 4 Byte", line_number, remove_white_spaces(line));
                
            }
            if (strncmp(remove_white_spaces(line), "double", 6) == 0) {
                sum_of_space_size +=sizeof(double);
                printf("\nLine %d: %s -> 8 Byte", line_number, remove_white_spaces(line));
                 
            }
            
        }
            
    }
    printf("\nSpace Complexity S(n) = + %d\n", sum_of_space_size);
    printf("\n**************************************************\n");
}
