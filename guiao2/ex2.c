#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


/*int main(){
	pid_t pai = getpid();
	pid_t filho = fork();
	printf("%d %d\n", pai, filho);
	sleep(1); 
	wait(NULL);
	return 0;
}*/

int main(){
	pid_t pai = getpid();
	pid_t filho = fork();
	printf("PID pai: %d\nPID filho: %d\n", pai, filho);
	sleep(1);
	wait(NULL);
	return 0;
}