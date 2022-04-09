#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char* argv){
	int sfd;
	int ofd;
	int flag = 1;

	if(strcmp(argv, "-i") == 0){
		argv++;
		sfd = open(argv, O_RDONLY);
		argv++;
		flag = 3;
	}

	if(strcmp(argv, "-o") == 0){
		argv++;
		ofd = open(argv, O_WRONLY|O_CREAT|O_TRUNC, 0666);
		argv++;
		flag = 5;
	}

	//argv[argc] = NULL;

	dup2(sfd, 0);
	dup2(ofd, 1);
	close(sfd);
	close(ofd);

	execvp(argv, &argv);

	return 0;
}