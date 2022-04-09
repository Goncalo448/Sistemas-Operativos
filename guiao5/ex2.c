#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
	int pd[2];
	char buffer[] = "ola filho\n";
	if(pipe(pd) == -1){
		perror("erro na criação do pipe\n");
		return 1;
	}

	if(fork() == 0){
		int bytesRead;
		close(pd[1]);

		while((bytesRead = read(pd[0], buffer, sizeof(buffer))) > 0){
			write(1, buffer, bytesRead);
		}
		close(pd[0]);

		_exit(0);
	}



	for(int i = 0; i != strlen(buffer); i++){
		buffer[i] = toupper(buffer[i]); //mete tudo em maiusculas
	}

	write(pd[1], buffer, strlen(buffer));
	close(pd[1]);

	wait(NULL);

	return 0;
}