#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char* argv[]){

	char buffer[1024];
	int i = 0;

	int fd = open("/etc/passwd", O_RDONLY);
	int fd2 = open("saida.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	int fd3 = open("erros.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	int ofd = dup(1);

	dup2(fd, 0);
	close(fd);
	dup2(fd2, 1);
	close(fd2);
	dup2(fd3, 2);
	close(fd3);

	execlp("wc", "wc", NULL);

	int bytesRead;
	while((bytesRead = read(0, &buffer, sizeof(buffer))) > 0){
		write(1, buffer, bytesRead);
	}

	dup2(ofd, 1);
	write(1, "terminei\n", 9);

	return 0;
}