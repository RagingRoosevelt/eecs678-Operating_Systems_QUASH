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


void execute(char* string)
{
	char command[BSIZE];
	char arguments[BSIZE];
	char background_flag[1];
}