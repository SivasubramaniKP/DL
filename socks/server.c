#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9090
#define BUFFER_SIZE 512

int main() {
        int server_fd, client_fd;
        struct sockaddr_in server_addr, client_addr;
        socklen_t socket_size = sizeof(client_addr);
        
        server_fd = socket(AF_INET, SOCK_STREAM, 0);

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        server_addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
                perror("Bind Failed");
                exit(1);
        }

        listen(server_fd, 4);

        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &socket_size);
 
        char buffer[BUFFER_SIZE] = "Hello from the server";
        send(client_fd, buffer, strlen(buffer), 0);


        close(server_fd);
        close(client_fd);

        return 0;
}
