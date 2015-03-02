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
			printf("Invalid path name. Please be careful.\n");
		}
	}

}