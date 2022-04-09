#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]){
	char buffer[64] = "./ex3 ls pwd"; 
	int i = 0;
	int size = 10;
	char *delim = " ";
	char *token = strtok(buffer, delim);
	char **args = malloc(sizeof(char*)*size);

	
	while(token != NULL){
		if(strcmp(token, argv[0]) != 0){
			args[i] = token;
			i++;
			if(i == size-2){
				size *= 2;
				args = realloc(args, sizeof(char*)*size);
			}
		}
		token = strtok(NULL, delim);
	}

	args[i] = NULL;
	
	pid_t pid = fork();
	int status;
	int ret;
	if(pid == 0){
		for(int k = 0; k < i; k++){
			ret = execvp(args[k], args);
			perror(args[k]);
			_exit(1);
		}
	}

	wait(&status);

	if(WIFEXITED(status)){
		return WEXITSTATUS(status);
	}else{
		return 1;
	}
}