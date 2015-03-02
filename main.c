#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>

#include "execute.c"

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


// Needs more testing
void cd(char* newpath)
{
	if (newpath == NULL)
	{
		chdir(getenv("HOME"));
	}
	else
	{
		if(chdir(newpath) == -1)
		{
			// This part definitely happens.
			printf("Invalid path name. Please be careful.");
		}
	}
}


int main(int argc, char **argv,char **envp)
{
	char current_cmd[BSIZE];
	char current_dir[BSIZE];
	
	printf("QUASH>");
	gets(current_cmd);
	
	/* set initial directory */
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		perror("getcwd() error");
	
	
	while (1)
	{		
		/* exit & quit command */
		if ((strcmp(current_cmd, "exit") == 0) || (strcmp(current_cmd, "quit") == 0))
		{
			break;
		
		
		} 
		/* pwd command */
		else if (strcmp(current_cmd, "pwd") == 0)
		{
			char temp[BSIZE];
			strcpy(temp, current_dir);
			printf(strcat(temp, "\n"));
		}
		
		printf("QUASH>");
		scanf("%s", &current_cmd);
		
	}

	return 0;
}