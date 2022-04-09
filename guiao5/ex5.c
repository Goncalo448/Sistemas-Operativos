#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
	int pipe1[2], pipe2[2], pipe3[2];
	if(pipe(pipe1) == -1){
		perror("Erro na criação do pipe!\n");
		return 1;
	}

	if(fork() == 0){
		close(pipe1[0]);
		dup2(pipe1[1], 1);
		close(pipe1[1]);
		execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
		_exit(1);
	}

	close(pipe1[1]);

	if(pipe(pipe2) == -1){
		perror("Erro na criação do pipe!\n");
		return 1;
	}

	if(fork() == 0){
		close(pipe2[0]);
		dup2(pipe1[0], 0);
		close(pipe1[0]);
		dup2(pipe2[1], 1);
		close(pipe2[1]);
		execlp("cut", "cut", "-f7", "-d:", NULL);
		_exit(1);
	}

	close(pipe1[0]);
	close(pipe2[1]);

	if(pipe(pipe3) == -1){
		perror("Erro na criação do pipe!\n");
		return 1;
	}

	if(fork() == 0){
		close(pipe3[0]);
		dup2(pipe2[0], 0);
		close(pipe2[0]);
		dup2(pipe3[1], 1);
		close(pipe3[1]);
		execlp("uniq", "uniq", NULL);
		_exit(1);
	}

	close(pipe2[0]);
	close(pipe3[1]);

	if(fork() == 0){
		dup2(pipe3[0], 0);
		close(pipe3[0]);
		execlp("wc", "wc", "-l", NULL);
		_exit(1);
	}

	close(pipe3[0]);

	wait(NULL);

	return 0;
}