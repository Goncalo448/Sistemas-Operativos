#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
	int fd = open("fifo", O_RDONLY, 0666);
	if(fd == -1){
		perror("fifo");
		return 1;
	}

	char buffer[1024];

	while(read(fd, buffer, sizeof(buffer)) > 0){
		write(1, buffer, sizeof(buffer));
	}

	close(fd);

	return 1;
}