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

//This is task 1
void executionInAction (void)
{
	int shmid_1, shmid_2, value_1;
	int *addr_1;
	int*addr_2;
	int value_2;
	float valuef;
	shmid_1 = shmget(1234, 10, (IPC_CREAT|0666));
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
	//*addr_1 = rand();
	value_1 = rand();
	*addr_1 = value_1;
	shmid_2 = shmget(5678, 10, (IPC_CREAT|0666));
	if(shmid_2 == -1)
	{
		fprintf(stderr,"Error Creating Mem. Segment\n");
		exit(1);
	}
	addr_2 = shmat(shmid_2, NULL, 0);
	if(addr_2 == (int*)-1)//
	{
			fprintf(stderr,"Error Attaching to Shared Memory\n");
		exit(1);
	}
	value_2 = rand();
	valuef = (float)value_2/10000;
	*addr_2 = value_2;
    int i;
    long long int           ns; // Milliseconds
    time_t          s;  // Seconds
    struct timespec tstart,tend;
    
    
    //clock_gettime(CLOCK_MONOTONIC, &tstart);
    usleep(20000); //20000 us =20ms  in reality usleep is blocking so it goes to wait state instead of run
    clock_gettime(CLOCK_MONOTONIC, &tend);

    printf("\nTask 1: PID %d  ", getpid());
    printf("Executed at: %ld ns  ",
            	((int64_t) tend.tv_sec * 1000000000
	   	+ (int64_t) tend.tv_nsec)	    
	);
	printf("Integer: %d\t  ", *addr_1);
	printf("Floating Number: %f\n ", valuef);

	if(shmctl(shmid_1,IPC_RMID,NULL) != 0)
	{
		printf("Error Removing Shared Memory Segment (1)\n");
		exit(1);
	}
	if(shmctl(shmid_2,IPC_RMID,NULL) != 0)
	{
		printf("Error Removing Shared Memory Segment (2)\n");
		exit(1);
	}
//and task 1 end s here
}
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
