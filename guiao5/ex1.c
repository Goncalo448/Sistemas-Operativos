#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char* argv[]){
	int pd[2];
	char buffer[] = "ola filho\n";
	if(pipe(pd) == -1){
		perror("erro na criação do pipe");
		return 1;
	}

	if(fork() == 0){
		int bytesRead;
		close(pd[1]);

		bytesRead = read(pd[0], buffer, sizeof(buffer));
		close(pd[0]);
		write(1, buffer, bytesRead);
		_exit(0);
	}

	sleep(5);

	for(int i = 0; i != strlen(buffer); i++){
		buffer[i] = toupper(buffer[i]); //mete tudo em maiusculas
	}

	write(pd[1], buffer, strlen(buffer));
	close(pd[1]);

	return 0;
}