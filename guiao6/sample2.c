#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char* argv[]){

	int fd = open("fifo", O_WRONLY, 0666);
	if(fd == -1){
		perror("fifo");
		return 1;
	}

	char buffer[1024];
	while(read(0, buffer, sizeof(buffer)) > 0){
		write(fd, buffer, sizeof(buffer));
	}

	close(fd);

	return 0;
}