


#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <unistd.h>

void* runner(void *);
void catch_alarm(int sig);

int main(int argc, char* argv[]){
	pthread_t scheduler;

	pthread_create(&scheduler, NULL, runner, NULL);

	sleep(10);
	printf("signaling \n");
	pthread_kill(scheduler, SIGUSR1);
	sleep(10);
	printf("signaling \n");
	pthread_kill(scheduler, SIGUSR1);
	// sleep(2);
	printf("signaling \n");
	pthread_kill(scheduler, SIGUSR1);

	pthread_join(scheduler, NULL);

	return 0;
}
void* runner(void *){
  	sigset_t mask, oldset;
	struct timespec tv;
	int retval;
	
	 //signal handling stuff
  	signal (SIGUSR1, catch_alarm);

  	//blcok signusr until in pselect
  	sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, &oldset);

	/* Wait up to five seconds. */
	tv.tv_sec = 5;
	tv.tv_nsec = 0;
  	
	while(true){
		retval = 0;

		retval = pselect(0, NULL, NULL, NULL, &tv, &oldset);
		if(retval < 0){
          printf("Got SIGUSR1\n");
		}
		else{
			printf("Dat timeout\n");
		}
		//reset tv
		  tv.tv_sec = 5;
		  tv.tv_nsec = 0;
	}
	return 0;
}
void catch_alarm (int sig){
	printf("sighandler\n");
  signal (sig, catch_alarm);
}