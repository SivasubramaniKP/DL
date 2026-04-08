

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9090
#define BUFFER_SIZE 512

int main() {
        int server_fd;
        struct sockaddr_in server_addr;

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);

        char server_ip[] = "127.0.0.1";
        inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

        connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

        char buffer[BUFFER_SIZE];
        read(server_fd, buffer, BUFFER_SIZE);

        printf("The server has sent the message %s", buffer);

        close(server_fd);
        return 0;
}
