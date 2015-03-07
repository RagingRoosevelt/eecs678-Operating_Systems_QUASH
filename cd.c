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


// Needs more testing
void cd(char* buffer)
{
	// Clear out the newline character at the end
	int len=strlen(buffer);
	if (buffer[len-1]=='\n'){
		buffer[len-1] = '\0';
	}
	
	if ((strcmp(buffer,"cd")==0) || (strcmp(buffer,"cd ")==0))
	{
		chdir(getenv("HOME"));
	}
	else
	{
		// remove first three characters of buffer (should be "cd ")
		if (strncmp(buffer,"cd ",3)==0){
			buffer+=3;			
		}
		
		if(chdir(buffer) == -1)
		{
			// This part definitely happens.
			printf("Invalid path name. Please be careful.\n");
		}
	}

}