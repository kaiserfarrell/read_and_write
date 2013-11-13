#include <unistd.h>
#include <stdio.h>
#include <sched.h>

main()
{	struct sched_param p;
	int p1,p2,p3;
			
	p1=fork();	
	
	if (p1==0)
	{	
	p.sched_priority= 70;	sched_setparam(getpid(),&p);
	
	//settinf RT FIFO scheduler with priority 90    
	sched_setscheduler(getpid(),SCHED_FIFO,&p);
	//printf("Master\n");
	execl("p1","/usr/bin/gnome-terminal","-1",NULL);	}

	else if (p1 >0)
	{	printf("P1: Writer\n");	}
	else {	printf("fork P1 fail\n");	}

	p2=fork();
	if (p2==0)
	{	p.sched_priority= 70;	
		sched_setparam(getpid(),&p);
	
		//settinf RT FIFO scheduler with priority 90    
		sched_setscheduler(getpid(),SCHED_FIFO,&p);

		execl("p2","/usr/bin/gnome-terminal","-1",NULL);	}

	else if (p2>0)
	{	printf("P2: Reader\n");	}
	else {	printf("fork P2 fail\n");	}
	//---------------------------------------------------------------
	p3=fork();	
	
	if (p3==0)
	{	
	p.sched_priority= 70;	sched_setparam(getpid(),&p);
	
	//settinf RT FIFO scheduler with priority 90    
	sched_setscheduler(getpid(),SCHED_FIFO,&p);
	//printf("Master\n");
	execl("p3","/usr/bin/gnome-terminal","-1",NULL);	}

	else if (p3 >0)
	{	printf("P3: Reader\n");	}
	else {	printf("fork P3 fail\n");	}
	//---------------------------------------------------------------
}
