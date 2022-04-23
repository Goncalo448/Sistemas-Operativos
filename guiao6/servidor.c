#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char* argv[]){

	int fd = open("log.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	if(fd == -1){
		perror("log");
		return 1;
	}

	int pipe = open("fifo", O_RDONLY, 0666);
	if(pipe == -1){
		perror("fifo");
		return 1;
	}

	char buffer[512];
	while(read(pipe, buffer, sizeof(buffer)) > 0){
		write(fd, buffer, sizeof(buffer));
	}

	close(pipe);
	close(fd);

	return 0;
}