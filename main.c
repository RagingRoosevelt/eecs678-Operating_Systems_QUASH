#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>

#include "execute.c"
#include "cd.c"

#define BSIZE 256

using namespace std;

/*
* [ ] Run executables without arguments (10)
* [ ] Run executables with arguments (10)
* [ ] set for HOME and PATH work properly (5)
* [x] exit and quit work properly (5)
* [~45%] cd (with and without arguments) works properly (5)
* [ ] PATH works properly. Give error messages when the executable is not found (10)
* [ ] Child processes inherit the environment (5)
* [ ] Allow background/foreground execution (&) (5)
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


int main(int argc, char **argv,char **envp)
{
	
	printf("Welcome to QUASH\n");
	cout << "Home Directory:    " << getenv("HOME") << "\n";
	cout << "Current Directory: " << getcwd(NULL, 0) << "\n\n";
	cout << "PATH: " << getenv("PATH") << "\n\n";
	
	char user_input[BSIZE];
	char current_cmd[BSIZE];
	char current_args[BSIZE][BSIZE];
	char temp[BSIZE];
	
	
	while ((strcmp(user_input, "exit")!=0) && (strcmp(user_input, "quit")!=0))
	{		
		printf(strcat(getcwd(NULL, 0), ">"));
		fgets(user_input, sizeof(user_input), stdin);
		
		/* 
		 *tokenize user input into command and arguments 
		 */
		/* get the first token */
		char *token;
		strcpy(current_cmd, "");
		for (int i=0; i<BSIZE; i++)
		{
			strcpy(current_args[i], "");
		}
		token = strtok(user_input, " \n");
		strncpy(current_cmd, token, sizeof(current_cmd)-1);
		printf( "command: %s\n", current_cmd );
		token = strtok(NULL, " \n");
		/* walk through other tokens */
		int arg_count = 0;
		while( token != NULL ) 
		{
			//printf( "Argument: %s\n", token );
			strncpy(current_args[arg_count], token, sizeof(current_args[arg_count])-1);
			/*strncpy(temp, token, sizeof(temp)-1);
			strcat(current_args, temp);
			strcat(current_args, " ");*/
			token = strtok(NULL, " \n");
			arg_count++;
		}
		for (int i=0; i<arg_count; i++)
		{
			printf("Arguments: '%s'\n", current_args[i]);
		}
		
		/* 
		 * pwd command 
		 */
		if (strcmp(current_cmd, "pwd") == 0)
		{
			if (getcwd(temp, sizeof(temp)) == NULL)
			{
				perror("getcwd() error");
			}
		
			printf(strcat(temp, "\n"));
		} else if (strcmp(current_cmd, "cd") == 0) {
			cd(current_args[0]);
		}
		
	}

	return 0;
}