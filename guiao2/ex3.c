#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
	
	for(int i = 0; i < 10; i++){
		if(fork() == 0){
			printf("Filho: %d, Pai: %d\n", getpid(), getppid());
			_exit(1);
		}else{
			int exit_status;
			wait(&exit_status);
			printf("Exit: %d\n", WEXITSTATUS(exit_status));
		}
	}

	return 0;
}