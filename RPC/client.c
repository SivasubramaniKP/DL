
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <string.h>
#include "rpc.h"

int rpc_call(const char* server_ip, const char* func_name, int arg1, int arg2, int *result) {
        int sock_fd;
        struct sockaddr_in server_addr;
        char buffer[BUFFER_SIZE];

        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_fd < 0) {
                perror("socket");
                exit(1);
        }

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);

        if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
                perror("inet_pton");
                exit(1);
        }

        if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
                perror("Connect");
                exit(1);
        }

        snprintf(buffer, BUFFER_SIZE, "%s %d %d", func_name, arg1, arg2);

        write(sock_fd, buffer, strlen(buffer) + 1);

        RpcResponse resp;
        read(sock_fd, &resp, sizeof(RpcResponse));
        close(sock_fd);

        if(resp.success) {
                *result = resp.result;
                return 0;
        } else {
                fprintf(stderr, "RPC error %s\n", resp.error_message);
                return -1;
        }

}

int main(int argc, char *argv[]) {
        if (argc != 5) {
                perror("Invalid input");
                return 1;
        }

        char *server_ip = argv[1];
        char *func_name = argv[2];
        int arg1 = atoi(argv[3]);
        int arg2 = atoi(argv[4]);

        printf("%s %s %d %d", server_ip, func_name, arg1, arg2);
        int result;

        if (rpc_call(server_ip, func_name, arg1, arg2, &result) == 0) {
                printf("RPC Call is successful result = %d", result);
        } else {
                printf("RPC call failed");
        }
        
        return 0;

}



