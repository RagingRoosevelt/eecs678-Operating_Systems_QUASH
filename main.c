#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define BSIZE 256

using namespace std;

/*
 * [x] Run executables without arguments (10)
 * [x] Run executables with arguments (10)
 * [ ] set for HOME and PATH work properly (5)
 * [x] exit and quit work properly (5)
 * [x] cd (with and without arguments) works properly (5)
 * [ ] PATH works properly. Give error messages when the executable is not found (10)
 * [x] Child processes inherit the environment (5)
 * [x] Allow background/foreground execution (&) (5)
 * [ ] Printing/reporting of background processes, (including the jobs command) (10)
 * [ ] Allow file redirection (> and <) (5)
 * [ ] Allow (1) pipe (|) (10)
 * [ ] Supports reading commands from prompt and from file (10)
 * [ ] Report (10)
 *
 * Bonus points:
 * [ ] Support multiple pipes in one command (10)
 * [ ] kill command delivers signals to background processes. The kill
 * command has the format: kill SIGNUM, JOBID, where SIGNUM is an integer
 * specifying the signal number, and JOBID is an integer that specifies
 * the job that should receive the signal (5)
 */

#include "execute.c"
#include "cd.c"
#include "job.c"

/* Handles reading input from prompt
 */
char* accept(char* line) {
	read(0, line, BSIZE);
	return line;
}

/* Types of commands to receive from prompt
 */
typedef enum {
	regular, pipes, in, out
} type;

/* Structure containing relevant info for command
 * Populated by parse_raw_input
 */
typedef struct{
	char** cmdbuf;
	int arg_count;
	char **args;
	type command_type;
	int run_in_background;
	char target[BSIZE];
} command;

/* Parses ran user input into command structure
 */
command* parse_raw_input(char* buffer, char **args) {
	
	//Temporary stuff
	char raw[BSIZE];
	char* temp;
	char* token;
	char** cmdbuf = (char**) malloc(sizeof(char*) * BSIZE);
	char** argv2;
	int arg_count = 0;
	int run_in_background;

	command* current_cmd;

	current_cmd = (command*) malloc(sizeof(command));
	
	
	//Copy buffer to raw to avoid messing with other stuff
	strcpy(raw, buffer);
	
	//Tokenize on spaces
	token = strtok(raw, " \n");
	while (token != NULL ) {
		// Malloc a new string
		temp = (char*) malloc((strlen(token) * sizeof(char)) + 1);
		
		// Zero it out
		memset(temp, '\0', (strlen(token) * sizeof(char)) + 1);
		
		// Copy the contents of our token into temp
		strcpy(temp, token);
		
		// Set the cmdbuf array to the temp pointer freshly malloced
		cmdbuf[arg_count] = temp;
		
		// Clean temp pointer
		temp = NULL;
		
		//Tokenize again
		token = strtok(NULL, " \n");
		arg_count++;
	}

	// Run detection for background operation
	if (arg_count != 0) {
		if (strcmp(cmdbuf[arg_count - 1], "&") == 0) {
			run_in_background = 1;
			cmdbuf[arg_count - 1][0] = '\0';
		} else {
			run_in_background = 0;
		}
	}
	
	//Trims the emoty slots of the cmdbuf array to avoid causing headaches 
	//when running commands with different amounts of arguments
	//I lost 3 hours until I realized this.
	argv2 = (char**) malloc(sizeof(char*) * (arg_count + 1));
	int i = 0;
	for (i = arg_count; i < BSIZE - 1; i++) {

		cmdbuf[arg_count] = '\0';
	}
	
	//Set our command to its contents
	(*current_cmd).arg_count = arg_count;
	(*current_cmd).run_in_background = run_in_background;
	(*current_cmd).cmdbuf = cmdbuf;
	(*current_cmd).command_type = regular;
	(*current_cmd).args = args;
	
	//Return the pointer to the malloced Command
	return current_cmd;
}


/* Main program
 */
int main(int argc, char **argv,char **envp) {
	
	printf("Welcome to QUASH\n");
	printf("Developed by Theodore S Lindsey & Samuel A Lamb\n");
	printf("Home Directory:    %s\n", getenv("HOME"));
	printf("Current Directory: %s\n\n", getcwd(NULL, 0));
	printf("PATH:              %s\n\n", getenv("PATH"));
	
	
	char line[BSIZE];
	char *buffer;
	char **args;
	char temp[BSIZE];
	
	command* commandOne;
	command* commandTwo;
	
	// string after |, <, or >
	char* pipe_useage;
	char* file_input;
	char* file_output;
	
	while (1)
	{	// display QUASH prompt and get user input.	
	  
		
		printf("%s> ",getcwd(NULL,0));
		fflush(stdout);
		// ensure line is empty
		memset(line, '\0', sizeof(line));
		// read in line
		buffer = accept(line);
		
		/* look for first occurrence of |, <, or > and 
		 * report on trailing string
		 */
		pipe_useage = strpbrk(buffer, "|");
		file_input = strpbrk(buffer, "<");
		file_output = strpbrk(buffer, ">");
		printf("pipe        :%s\n",pipe_useage);
		printf("in from file:%s\n", file_input);
		printf("out to file :%s\n", file_output);
		
		
		/* Figure out what commands to execute
		 */
		if ((strcmp(buffer,"exit\n")==0) || (strcmp(buffer,"quit\n")==0)){
			break;
		}else if (strncmp(buffer, "cd", 2) == 0) {
			cd(buffer);
		} else if (strncmp(buffer, "pwd",3)==0) {
			printf("%s\n",getcwd(NULL, 0));
		} else if (strcmp(buffer, "clear\n")==0) {
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		} else {
			if (file_input != NULL) {
				// input redirection, read input from file
				printf("input redirection, read input from file\n");
				#if 0
				// Tokenize to remove '<' and '\n', getting first the command
				char *token = strtok(buffer, "<\n");
				strcpy(temp, token);
				commandOne = parse_raw_input(temp, args);
				// Advance token to get input file
				token = strtok(NULL, "<\n");
				strcpy(temp, token);
				
				// Execute the command and output the result to a file
				//execute_output_to_file(&((*commandOne).cmdbuf), (*commandOne).run_in_background, (*commandOne).args, temp);
				
				// Reset variables
				strcpy(temp,"");
				free(commandOne);
				commandOne = NULL;
				#endif
			} else if ((file_output == NULL) && (pipe_useage == NULL)){
				// standard command
				printf("<standard command>\n");
				
				commandOne = parse_raw_input(buffer, args);
				execute(&((*commandOne).cmdbuf), (*commandOne).run_in_background, (*commandOne).args);
				memset(commandOne, 0, sizeof(*commandOne));
				memset(buffer, '\0', sizeof(buffer));
				// Reset command variable
				free(commandOne);
				commandOne = NULL;
				
			} else if ((file_output == NULL) && (pipe_useage != NULL)){
				// pipe only
				printf("<pipe only>\n");
				
			} else if ((file_output == NULL) && (pipe_useage == NULL)){
				// output redirection only
				printf("<output redirection only>\n");
				
			} else if ((file_output == NULL) && (pipe_useage != NULL)){
				// output redirection and pipe
				printf("<output redirection and pipe>\n");
			}
				
		
		}
	}
	return 0;
}
