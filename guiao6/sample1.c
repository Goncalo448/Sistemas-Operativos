#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char* argv[]){

	if(mkfifo("fifo", 0666) == -1){
		perror("fifo");
		return 1;
	}

	return 0;
}