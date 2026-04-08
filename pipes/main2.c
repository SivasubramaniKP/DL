#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	int p1[2];
	int p2[2];
	pipe(p1);
	pipe(p2);

	pid_t pid = fork();

	if(pid > 0) {
		char buffer[512];

		char operator = '-';
		int arg1 = 10;
		int arg2 = 10;
		printf("Inside parent process %d %d %c \n", arg1, arg2, operator);

		write(p1[1], &operator, sizeof(operator));
		write(p1[1], &arg1, sizeof(arg1));
		write(p1[1], &arg2, sizeof(arg2));

		int result;
		read(p2[0], &result, sizeof(result));

		wait(NULL);
		printf("Child has given me the result %d", result);
	} else {
		char operator; int arg1, arg2	;

		printf("inside child process \n");
		read(p1[0], &operator, sizeof(operator));
		read(p1[0], &arg1, sizeof(arg1));
		read(p1[0], &arg2, sizeof(arg2));

		printf("has read the args from parent\n");
		int result = -1;
		if(operator == '-') {
			result = arg1 - arg2;
		}

		write(p2[1], &result, sizeof(result));
	}

	return 0;

}
