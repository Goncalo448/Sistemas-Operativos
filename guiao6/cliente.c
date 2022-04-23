#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char* argv[]){

	int pipe = open("fifo", O_WRONLY, 0666);
	if(pipe == -1){
		perror("fifo");
		return 1;
	}

	char buffer[512];
	while(read(1, buffer, sizeof(buffer)) > 0){
		write(pipe, buffer, sizeof(buffer));
	}

	close(pipe);

	return 0;
}