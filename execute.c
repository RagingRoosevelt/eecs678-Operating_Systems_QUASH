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


void execute(char ***cmdbuf, int run_in_background, char **args)
{
	errno = 0;
	int status;
	pid_t pid;
	
	pid = fork();
	if (pid < 0){
		// thread creation failed
		printf("Error with fork");
		exit(1);
	} else if (pid==0){
		// child thread
		if (execvpe(**cmdbuf, *cmdbuf, args)<0){
			printf("error replacing process image: %s\n",strerror(errno));
			exit(1);
		}
	} else {
		// parent thread
		if (run_in_background == 0){
			while (wait(&status) != pid){}
		} else {
			printf("[1] %d\n",pid);
		}
	}
	return;
}

void execute_to_file(char ***cmdbuf, int run_in_background, char **args, char* file_out_path){
	errno = 0;
	int status;
	pid_t pid;
	pid = fork();
	if (pid < 0){
		// thread creation failed
		printf("Error with fork");
		exit(1);
	} else if (pid==0){
		// child thread
		FILE *file_out;
		file_out = fopen(file_out_path, "w");
		dup2(fileno(file_out), STDOUT_FILENO);
		fclose(file_out);
		if (execvpe(**cmdbuf, *cmdbuf, args)<0){
			printf("error replacing process image: %s\n",strerror(errno));
			exit(1);
		}
	} else {
		// parent thread
		if (run_in_background == 0){
			while (wait(&status) != pid){}
		} else {
			printf("[1] %d\n",pid);
		}
	}
	return;
}



void execute_from_file(char ***cmdbuf, int run_in_background, char **args, char* file_in_path){
	errno = 0;
	int status;
	pid_t pid;
	pid = fork();
	if (pid < 0){
		// thread creation failed
		printf("Error with fork");
		exit(1);
	} else if (pid==0){
		// child thread
		FILE *file_in;
		/* I'm a little lost. Why do we open a file, dupe STDIN, then immediately close the file again?
		*  This doesn't look like it should actually do anything. */
		file_in = fopen(file_in_path, "r");
		dup2(fileno(file_in), STDIN_FILENO);
		fclose(file_in);
		if (execvpe(**cmdbuf, *cmdbuf, args)<0){
			printf("error replacing process image: %s\n",strerror(errno));
			exit(1);
		}
	} else {
		// parent thread
		if (run_in_background == 0){
			while (wait(&status) != pid){}
		} else {
			printf("[1] %d\n",pid);
		}
	}
	return;
}