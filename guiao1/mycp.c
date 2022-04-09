#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

/*int main(int argc, char* argv[]){
	if(argc != 3){
		fprintf(stderr, "usage: %s source destination\n", argv[0]);
		return 1;
	}

	int sfd = open(argv[1], O_RDONLY); //ficheiro de origem
	if(sfd == -1){
		perror(argv[1]);
		return 1;
	}

	int dfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666);
	if(dfd == -1){
		perror(argv[2]);
		return 1;
	}

	int n;
	char c;
	while(1){
		n = read(sfd, &c, sizeof(c));
		if(n <= 0){
			break;
		}
		write(dfd, &c, n);
	}

	close(sfd);
	close(dfd);

	return 0;
}*/


int main(int argc, char* argv[]){

	if(argc != 3){
		fprintf(stderr, "Uso: %s [FILE] [FILE]", argv[0]);
		return 1;
	}

	int sfd = open(argv[1], O_RDONLY);
	if(sfd == -1){
		perror(argv[1]);
		return 1;
	}

	int dfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666);
	if(dfd == -1){
		perror(argv[2]);
		return 1;
	}

	int n;
	char c;
	while(1){
		n = read(sfd, &c, sizeof(c));
		if(n <= 0){
			break;
		}
		write(dfd, &c, n);
	}

	close(sfd);
	close(dfd);

	return 0;
}

//argc indica o nº de strings com que o comando foi exec


//gcc -Wall 





















