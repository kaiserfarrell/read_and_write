#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <sched.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

timer_t gTimerid;


void start_timer(void)
{

struct itimerspec value;

value.it_value.tv_sec = 4;
value.it_value.tv_nsec = 0;

value.it_interval.tv_sec = 4;
value.it_interval.tv_nsec = 0;

timer_create (CLOCK_REALTIME, NULL, &gTimerid);
timer_settime (gTimerid, 0, &value, NULL);

}

//This is task 2
void executionInAction (void)
{
    int i;
    long long            ns; // Milliseconds
    time_t          s;  // Seconds
    struct timespec tstart,tend;
	int shmid_1;
	int *addr_1;
	int integer;
	shmid_1 = shmget(1234, 10, IPC_CREAT | 0666);
	if(shmid_1 == -1)
	{
		fprintf(stderr,"Error Creating Mem. Segment\n");
		exit(1);
	}
	addr_1 = shmat(shmid_1, NULL, 0);
	if(addr_1 == (int*)-1)
	{
		fprintf(stderr,"Error Attaching to Shared Memory\n");
		exit(1);
	}
	integer = *addr_1;
	usleep(20000); //20000 us =20ms  in reality usleep is blocking so it goes to wait state instead of run
    clock_gettime(CLOCK_MONOTONIC, &tend);

    printf("Task 2: PID %d  ", getpid());
    printf("Executed at: %ld ns  ",
            	((int64_t) tend.tv_sec * 1000000000
	   	+ (int64_t) tend.tv_nsec)	    
	);
    printf("Integer: %d  \n",integer);

	if(shmctl(shmid_1,IPC_RMID,NULL) != 0)
	{
		printf("Error Removing Shared Memory Segment (1)\n");
		exit(1);
	}
}
//and task 2 end s here


void timer_callback(int sig)
{
  executionInAction();
 (void) signal(SIGALRM, timer_callback);
}

int main(int ac, char **av)
{
	(void) signal(SIGALRM, timer_callback);
    	start_timer();
    	while(1);
}
