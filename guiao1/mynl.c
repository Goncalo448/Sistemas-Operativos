#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>


ssize_t improved_readln(int fd, char *line, size_t size){
	
}


int main(int argc, char* argv[]){
	if(argc > 2){
		fprintf(stderr, "usage: %s or %s [FILE]", argv[0], argv[0]);
		return 1;
	}

	int sfd = 0;
	if(argc == 2){
		sfd = open(argv[1], O_RDONLY);
	}

	if(sfd == -1){
		perror(argv[1]);
		return 1;
	}

	char buffer[1024], buf[32];
	int bytes, cont = 1;
	while((bytes = improved_readln(sfd, buffer, 1024)) > 0){
		if(bytes == 1){
			write(1, "\n", 1);
		}else{
			sprintf(buf, "%6d ", cont);
			write(1, buf, 8);
			write(1, buffer, bytes);
			write(1, "\n", 1);
			cont++;
		}
	}

	return 0;
}