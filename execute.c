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
	
	
	sprintf(cmdbuf,"%s",current_cmd);
	sprintf(argbuf, current_args[0]);
	for (int i=1; i<arg_count; i++)
	{ 
		sprintf(argbuf, "%s %s", argbuf, current_args[i]); 
	}
	
	
	
	if (strcmp(cmdbuf, "") !=0 )
	{
	  printf("executing :%s %s",cmdbuf,argbuf);
		pid = fork();
		if(pid == 0)
		{
		  fflush(stderr);
			if (execlp(cmdbuf,cmdbuf,argbuf)<0){
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
