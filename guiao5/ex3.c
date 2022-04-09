#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
	int pd[2];
	if(pipe(pd) == -1){
		perror("Erro na criação do pipe!\n");
		return 1;
	}

	if(fork() == 0){
		close(pd[1]);
		dup2(pd[0], 0);
		close(pd[0]);
		execlp("wc", "wc", NULL);
		_exit(0);
	}

	close(pd[0]);
	int bytesRead;
	char buffer[5];
	while((bytesRead = read(0, buffer, sizeof(buffer))) > 0){
		write(pd[1], buffer, bytesRead);
	}

	close(pd[1]);
	wait(NULL);

	return 0;
}