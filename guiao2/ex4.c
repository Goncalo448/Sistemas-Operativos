#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(){
	char buffer[100];
	int status;
	pid_t pai = getpid();
	for(int i = 0; i < 10; i++){
		pid_t filho = fork();
		if(filho == 0){
			int size = snprintf(buffer, 64, "Filho: %d, Pai: %d\n", getpid(), getppid());
			if(write(1, buffer, size) != -1){
				_exit(0);
			}else{
				_exit(1);
			}
		}
	}

	for(int i = 0; i < 10; i++){
		pid_t pid = wait(&status);
		if(!WIFEXITED(status) || WEXITSTATUS(status)){
			return 1;
		}
	}

	return 0;
}