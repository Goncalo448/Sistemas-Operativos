#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
	int sfd = open("/etc/passwd", O_RDONLY);
	int ofd = open("saida.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	int efd = open("erros.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);

	int temp = dup(1);
	dup2(sfd, 0);
	close(sfd);
	dup2(ofd, 1);
	close(ofd);
	dup2(efd, 2);
	close(efd);

	int bytesRead;
	char buffer[1024];
	while((bytesRead = read(0, &buffer, sizeof(buffer))) > 0){
		write(1, buffer, bytesRead);
	}

	dup2(temp, 1);
	close(temp);
	write(1, "terminei\n", 9);

	return 0;
}