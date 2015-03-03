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
	char background_flag[1];
	char cmdbuf[BSIZE];
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
		 
		sprintf(cmdbuf, "%s", current_cmd);
		for (int i=0; i<arg_count; i++)
		{ 
			sprintf(cmdbuf, "%s %s", cmdbuf, current_args[i]); 
		}
		printf("%s\n",cmdbuf);
		
		/* swap fork binaries in order to execute the find command */
		/*if ( (execl(BASH_EXEC, BASH_EXEC, "-c", cmdbuf, (char *) 0)) < 0) {
		  fprintf(stderr, "\nError execing find. ERROR#%d\n", errno);
		  return EXIT_FAILURE;
		}*/
		return 1;
	 } else if (current_cmd[0]=='.')
	 {
		 // relative path
		 printf("relative path to binary\n");
	 } else
	 {
		 // must be in PATH
		 printf("binary in $PATH\n");
	 }
	 
	 return 0;
}