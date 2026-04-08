
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "rpc.h"

int add(int a, int b) {return a + b;}
int sub(int a, int b) {return a - b;}


typedef struct {
        char *name;
        int (*func)(int, int);
} RpcFunction;

RpcFunction Registry[] = {
        {"add", add},
        {"sub", sub},
        {"NULL", NULL}
};

int call_rpc(char *func_name, int a, int b, int *result) {
        for(int i = 0; i < 3; i++) {
                if(strcmp(func_name, Registry[i].name) == 0) {
                        *result = Registry[i].func(a, b);
                        return 1;
                }
        } 
        return 0;
}

void handle_client(int client_fd) {
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);

        read(client_fd, buffer, BUFFER_SIZE);

        char func_name[32];
        int arg1, arg2;
        sscanf(buffer, "%s %d %d", func_name, &arg1, &arg2);
        printf("%s %d %d", func_name, arg1, arg2);

        RpcResponse resp;
        resp.result = 0;
        resp.success = 0;

        strcpy(resp.error_message, "");

        int result;
        if(call_rpc(func_name, arg1, arg2, &result)) {
                resp.success = 1;
                resp.result = result;
        } else {
                snprintf(resp.error_message, sizeof(resp.error_message), "Function %s is not found", func_name);
        }

        write(client_fd, &resp, sizeof(RpcResponse));
        close(client_fd);

}

int main() {
        int server_fd, client_fd;

        struct sockaddr_in server_addr, client_addr;

        socklen_t addr_len = sizeof(client_addr);

        server_fd = socket(AF_INET, SOCK_STREAM, 0);

        if (server_fd < 0) {
                perror("socket");
                exit(1);
        }

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(PORT);

        if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
                perror("bind");
                exit(1);
        }
        
        listen(server_fd, 5);

        while(1) {
                client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
                if (client_fd < 0) {
                        perror("accept");
                        exit(1);
                }
                handle_client(client_fd);
        }

        close(server_fd);
        return 0;

}
