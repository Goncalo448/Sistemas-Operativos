#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>


#define MAX 100

struct pessoa{

	int idade;
	char nome[MAX];
};


int main(int argc, char* argv[]){

	if(argc != 4){
		fprintf(stderr, "Uso: %s [opção] [nome] [idade]", argv[0]);
		return 1;
	}

	struct pessoa p;
	int cont = 1;

	int fd = open("pessoas.bb", O_CREAT|O_RDWR, 0666);
	if(fd == -1){
		perror("pessoas.bb");
		return 1;
	}

	if(strcmp(argv[1], "-i") == 0){
		while(read(fd, &p, sizeof(p)) == sizeof(p)){
			cont++;
			if(strcmp(p.nome, argv[2]) == 0){
				fprintf(stderr, "O nome já existe!\n");
				return 0;
			}
		}
		strcpy(p.nome, argv[2]);
		p.idade = atoi(argv[3]);
		write(fd, &p, sizeof(p));
		printf("Posição %d\n", cont);
	}else if(strcmp(argv[1], "-u") == 0){
		while(read(fd, &p, sizeof(p)) == sizeof(p)){
			if(strcmp(p.nome, argv[2]) == 0){
				p.idade = atoi(argv[3]);
				write(fd, &p, sizeof(p));
				break;
			}
		}
	}else if(strcmp(argv[1], "-o") == 0){
		while(read(fd, &p, sizeof(p)) == sizeof(p)){
			if(cont == atoi(argv[2])){
				p.idade = atoi(argv[3]);
				write(fd, &p, sizeof(p));
				break;
			}
			cont++;
		}
	}

	close(fd);

	return 0;
}