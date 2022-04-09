#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>


int main(int argc, char* argv[]){
	if(argc > 2){
		fprintf(stderr, "usage: %s [optional: FILE]", argv[0]);
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

	ssize_t bytesRead;
	char buffer[1000];
	while((bytesRead = read(sfd, &buffer, 1000)) > 0){
		write(1, buffer, bytesRead);
	}

	close(sfd);
}