#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000
#define LINHAS 50
#define COLUNAS 500


int** geraMatriz(){
	int **matriz = malloc(sizeof(int)*LINHAS);
	srand(time(NULL));

	for(int i = 0; i < LINHAS; i++){
		matriz[i] = malloc(sizeof(int)*COLUNAS);
		for(int j = 0; j < COLUNAS; j++){
			matriz[i][j] = rand() % MAX;
		}
	}

	return matriz;
}


int main(int argc, char* argv[]){
	int** matriz = geraMatriz();
	int status;
	pid_t pid;

	for(int i = 0; i < LINHAS; i++){
		pid = fork();
		if(pid == 0){
			for(int j = 0; j < COLUNAS; j++){
				if(atoi(argv[1]) == matriz[i][j]){
					_exit(1);
				}
			}
			_exit(0);
		}
	}

	for(int i = 0; i < LINHAS; i++){
		wait(&status);
		if(WEXITSTATUS(status) || !WIFEXITED(status)){
			break;
		}
	}

	if(WIFEXITED(status)){
		if(WEXITSTATUS(status)){
			char buffer[64];
			int size = snprintf(buffer, 64, "O número %s existe na matriz.\n", argv[1]);
			if(write(1, buffer, size) == -1){
				return 1;
			}
		}else{
			char buffer[64];
			int size = snprintf(buffer, 64, "O número %s não existe na matriz.\n", argv[1]);
			if(write(1, buffer, size) == -1){
				return 1;
			}
		}
	}

	if(WIFEXITED(status)){
		return 0;
	}else{
		return 1;
	}
}
