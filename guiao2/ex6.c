#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000
#define LINHAS 10
#define COLUNAS 50


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


/*int main(int argc, char* argv[]){
	int** matriz = geraMatriz();
	int status;
	pid_t pid;
	// o {0} inicializa o array com todos os indices a zero.
	int index[LINHAS] = {0};
	pid_t pids[LINHAS];
	int flag = 0;


	for(int i = 0; i < LINHAS; i++){
		pid = fork();
		if(pid == 0){
			for(int j = 0; j < COLUNAS; j++){
				if(atoi(argv[1]) == matriz[i][j]){
					_exit(1);
				}
			}
			_exit(0);
		}else{
			pids[i] = pid;
		}
	}

	for(int i = 0; i < LINHAS; i++){
		waitpid(pids[i], &status, 0);

		if(!WIFEXITED(status)){
			break;
		}

		if(WEXITSTATUS(status)){
			index[i] = 1;
			flag = 1;
		}
	}

	if(WIFEXITED(status)){
		if(flag == 1){
			char buffer[LINHAS*2];
			int size = 0;
			for(int i = 0; i < LINHAS; i++){
				if(index[i]){
					size += snprintf(buffer+size, sizeof(buffer)-size, "%d ", i);
				}
			}

			size += snprintf(buffer+size, sizeof(buffer)-size, "\n");

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
}*/


int main(int argc, char* argv[]){
	
	int** matriz = geraMatriz();
	pid_t pid;
	int status;
	pid_t pids[LINHAS];
	int index[LINHAS] = {0};
	int flag = 0;

	for(int i = 0; i < LINHAS; i++){
		pid = fork();
		if(pid == 0){
			for(int j = 0; j < COLUNAS; j++){
				if(atoi(argv[1]) == matriz[i][j]){
					_exit(1);
				}
			}
			_exit(0);
		}else{
			pids[i] = pid;
		}
	}

	for(int i = 0; i < LINHAS; i++){
		waitpid(pids[i], &status, 0);

		if(!WIFEXITED(status)){
			break;
		}

		if(WEXITSTATUS(status)){
			index[i] = 1;
			flag = 1;
		}
	}

	if(WIFEXITED(status)){
		if(flag == 1){
			char buffer[LINHAS*2];
			int size = 0;
			for(int i = 0; i < LINHAS; i++){
				if(index[i]){
					size += snprintf(buffer+size, sizeof(buffer)-size, "%d ", i);
				}
			}

			size += snprintf(buffer+size, sizeof(buffer)-size, "\n");
			if(write(1, buffer, size) == -1){
				return 1;
			}
		}else{
			char buffer[64];
			int size = snprintf(buffer, 64, "O número %s não existe na matriz.\n", argv[1]);
			if(write(1, buffer, 64) == -1){
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
