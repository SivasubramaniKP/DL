#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};
    
    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    // Configure server address (IP of guest1)
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.100");  // Guest1 IP
    
    // Connect to server
    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    // Send message
    char *message = "Hello from Client Guest!";
    send(sock, message, strlen(message), 0);
    printf("Message sent\n");
    
    // Receive response
    read(sock, buffer, sizeof(buffer));
    printf("Server response: %s\n", buffer);
    
    close(sock);
    return 0;
}
