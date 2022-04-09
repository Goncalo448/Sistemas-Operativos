#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[]){
	int pd[2][2];
	if(pipe(pd[0]) == -1){
		perror("Erro na criação do pipe!\n");
		return 1;
	}

	if(fork())
}