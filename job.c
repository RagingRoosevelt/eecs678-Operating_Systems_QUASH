
#define BSIZE 256

using namespace std;

struct job {
	int jobID, jobpid;
	// pid_t jobpid; Better?
	char jobcommand[BSIZE];
	char jobargs[BSIZE][BSIZE]}
	bool background;
};