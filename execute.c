#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>

#define BSIZE 256

using namespace std;


int execute(char current_cmd[BSIZE], char current_args[BSIZE][BSIZE], int arg_count)
{
	int status=0;
	pid_t pid;
	char background_flag[1];
	char cmdbuf[BSIZE];
	char argbuf[BSIZE];
	/* 
	 * Determine if command is 
	 * 1) a relative path to a binary, 
	 * 2) an absolute path to a binary, 
	 * 3) or a program in PATH
	 */
	if (current_cmd[0]=='/')
	{
		// absolute path to binary
		printf("absolute path to binary\n");
		
		sprintf(cmdbuf,"%s",current_cmd);
		sprintf(argbuf, current_args[0]);
		for (int i=1; i<arg_count; i++)
		{ 
			sprintf(argbuf, "%s %s", argbuf, current_args[i]); 
		}
		printf("%s\n",argbuf);
		return 1;
	 } else if (current_cmd[0]=='.')
	 {
		// relative path
		printf("relative path to binary\n");
		
		sprintf(cmdbuf,"%s",current_cmd);
		sprintf(argbuf, current_args[0]);
		for (int i=1; i<arg_count; i++)
		{ 
			sprintf(argbuf, "%s %s", argbuf, current_args[i]); 
		}
		printf("%s\n",argbuf);
		return 1;
	 } else
	 {
		 // must be in PATH
		printf("binary in $PATH\n");
		
		/* Tokenize path into individual strings
		 */
		char *token;
		char path[BSIZE][BSIZE];
		char str[BSIZE];
		strncpy(str,getenv("PATH"),sizeof(str)-1);
		token = strtok(str, ":");
		int path_count=0;
		while( token != NULL ) 
		{	// Extract current token to next element of the argument array
			strncpy(path[path_count], token, sizeof(path[path_count]-1));
			// Advance token location
			token = strtok(NULL, ":");
			path_count++;
		}
		
		/* search for command in current directory of PATH
		 */
		for (int i=0; i<path_count; i++)
		{
			sprintf(str,"");
			sprintf(str,"%s/%s",path[i],current_cmd);
			printf("trying {%s}\n",str);
			if (access(str, F_OK) != -1)
			{
				// file exists
				printf("binary found in {%s}\n",str);
				break;
			}
		}
		if (strncmp(str, "",sizeof(str))==0)
		{
			return 0;
		} else {
			sprintf(cmdbuf,"%s",str);
			sprintf(argbuf, current_args[0]);
			for (int i=1; i<arg_count; i++)
			{ 
				sprintf(argbuf, "%s %s", argbuf, current_args[i]); 
			}
			printf("executing :%s %s\n",cmdbuf,argbuf);
		}
		
	}
	
	if (strcmp(cmdbuf, "") !=0 )
	{
		pid = fork();
		if(pid == 0)
		{
			if (execl(cmdbuf,cmdbuf,argbuf)<0){
				fprintf(stderr, "\nError execing find. ERROR#%d\n");
			}
			status=1;
			return status;
		} else {
			int i;
			while ((i = wait(&status)) > 0)
			{}
		}
		
	}
}