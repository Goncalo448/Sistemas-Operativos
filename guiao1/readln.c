#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>


/*ssize_t readln(int fd, char *line, size_t size){
	char c;
	ssize_t bytesRead = 0;
	while(bytesRead < size && read(fd, &c, 1) > 0){
		line[bytesRead] = c;
		bytesRead++;
		if(c == '\n'){
			break;
		}
	}
	return bytesRead;
}*/


