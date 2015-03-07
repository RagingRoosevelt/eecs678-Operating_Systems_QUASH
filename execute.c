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


int execute(char ***cmdbuf, int run_in_background, char **args)
{
	int status;
	pid_t pid;
	
	pid = fork();
	if (pid < 0){
		// thread creation failed
		printf("Error with fork");
	} else if (pid==0){
		// child thread
		execvpe(**cmdbuf, *cmdbuf, args);
	} else {
		// parent thread
		if (run_in_background == 0){
			while (wait(&status) != pid){}
		} else {
			printf("[1] %d\n",pid);
		}
	}
}