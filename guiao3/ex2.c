#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
	if(argc != 1){
		fprintf(stderr, "Uso: %s\n", argv[0]);
		return 1;
	}

	int status;
	pid_t pid = fork();
	int ret;
	if(pid == 0){
		ret = execlp("ls", "ls", "-l", NULL);
		perror("ls");
		_exit(EXIT_FAILURE);
	}
	wait(&status);

	if(WIFEXITED(status)){
		return WEXITSTATUS(status);
	}else{
		return 1;
	}
}