#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024] = {0};
    socklen_t addr_len = sizeof(client_addr);
    
    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces
    server_addr.sin_port = htons(8080);
    
    // Bind socket
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    // Listen for connections
    listen(server_fd, 3);
    printf("Server listening on port 8080...\n");
    
    // Accept connection from guest machine
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    printf("Client connected from %s:%d\n", 
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    
    // Receive and send data
    read(client_fd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);
    
    char *response = "Hello from Server Guest!";
    send(client_fd, response, strlen(response), 0);
    
    close(client_fd);
    close(server_fd);
    return 0;
}
