#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int id;
	char title[50];
	char desc[100];
} Note;

char* get_string(Note note) {
	char *msg = (char *)malloc(sizeof(char) * 200);
	sprintf(msg, "Note id : %d\nNote title: %s\nNote description: %s\n\n", note.id, note.title, note.desc);
	return  msg;
}


int main () {
	int fd[2];
	pipe(fd);

	fcntl(fd[0], F_SETFL, O_NONBLOCK);
	fcntl(fd[1], F_SETFL, O_NONBLOCK);

	pid_t pid = fork();

	if(pid == 0) {
		Note notes[3] = {
			{1, "First note", "first descr"}	,
			{2, "second note", "second desc"},
			{3, "third note", "third desc"}
		};

		for(int i = 0; i < 3; i++)  {
			char *msg = get_string(notes[i]);
			ssize_t bytes = write(fd[1], msg, strlen(msg)+ 1);
			if(bytes == -1) {
				if(errno == EAGAIN) {
					printf("PIPE IS FULL\n\n");
				} else perror("write");
			} else {
				printf("Successfully written %s", msg);	
			}
			wait(NULL);
			usleep(300000);
		}
	} else {
		for(int i = 0; i < 3; i++) {
			char buffer[200];
			ssize_t bytes = read(fd[0], buffer, sizeof(buffer));
			if(bytes == -1) {
				if (errno == EAGAIN) {
					printf("Pipe is empty\n");
				} else perror("read");
			} else printf("RECEIVED %s\n\n", buffer);

			usleep(300000);
		}
	}

}
