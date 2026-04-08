
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <errno.h>
int main() {
	int pipefd[2]	;
	pipe(pipefd);

	fcntl(pipefd[0], F_SETFL, O_NONBLOCK);
	fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

	pid_t pid = fork();

	if(pid == 0) {
		for(int i = 0 ; i <= 5; i++ ) {
			char msg[50];
			sprintf(msg, "Message : %d", i);

			ssize_t bytes = write(pipefd[1], msg, strlen(msg) + 1);

			if(bytes == -1) {
				if(errno == EAGAIN) {
					printf("Child: pipe is full");
				}
			} else {
				printf("Child has sent %s \n", msg);
			}
			usleep(500000);
		}	

	}
	else {
		char buffer[100];
		for(int i = 0; i <= 10; i++) {
			ssize_t bytes = read(pipefd[0], buffer, sizeof(buffer));
			if (bytes == -1) {
				if(errno == EAGAIN) {
					printf("No data to fetch for the parent");
				}
			} else {
				printf("Parent has receieved : %s \n", buffer)	;
			}
			usleep(300000);
		}	
		wait(NULL);

	}
}
