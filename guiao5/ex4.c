#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
	int pd[2];
	if(pipe(pd) == -1){
		perror("Erro na criação do pipe!\n");
		return 1;
	}

	if(fork() == 0){
		close(pd[0]);
		dup2(pd[1], 1);
		close(pd[1]);
		execlp("ls", "ls", "/etc", NULL);
		_exit(1);
	}

	close(pd[1]);

	if(fork() == 0){
		dup2(pd[0], 0);
		close(pd[0]);
		execlp("wc", "wc", "-l", NULL);
		_exit(1);
	}

	close(pd[0]);

	if(wait(NULL) == -1){
		fprintf(stderr, "Error!\n");
	}

	if(wait(NULL) == -1){
		fprintf(stderr, "Error!\n");
	}

	return 0;
}