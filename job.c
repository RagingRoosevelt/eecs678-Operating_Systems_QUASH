
#define BSIZE 256
#define MAXJOBS 100

using namespace std;

struct job {
	int jobID, jobpid;
	// pid_t jobpid; Better?
	char jobcommand[BSIZE];
	char jobargs[BSIZE][BSIZE];
	bool background;
};

// I know this is icky.
job joblist[MAXJOBS];
int numjobs = 0;
int numBGjobs = 0;

