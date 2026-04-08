#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	int pipefd[2];
	pipe(pipefd);
	
	pid_t pid = fork();

	if(pid == 0) {
		printf("In child process\n");
		char buffer[512];
		read(pipefd[0], buffer, sizeof(buffer));
		printf("Parent has sent me %s\n", buffer);
	} else {
		char msg[] = "This is my message to my lovely child process"	;
		write(pipefd[1], msg, strlen(msg) + 1);
		wait(NULL);
	}

	return 0;
}
