#include <unistd.h>
#include <stdio.h>


int main(int argc, char* argv[]){
	if(argc != 1){
		fprintf(stderr, "Uso: %s\n", argv[0]);
		return 1;
	}

	int ret;
	ret = execlp("ls", "ls", "-l", NULL);
	printf("Erro. Resultado do ret = %d\n", ret);
	perror("reached return");
	return 0;
}