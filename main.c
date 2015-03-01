#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/wait.h>

using namepace std;

/*
* [ ] Run executables without arguments (10)
* [ ] Run executables with arguments (10)
* [ ] set for HOME and PATH work properly (5)
* [ ] exit and quit work properly (5)
* [ ] cd (with and without arguments) works properly (5)
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
	// Until I can figure out inputs in C, autoquit (I hope)
	char *current_cmd = "exit";
	while (1)
	{
		if ((strcmp(current_cmd, "exit") == 0) || (strcmp(current_cmd, "quit") == 0))
		{
			break;
		}
	}

	return 0;
}