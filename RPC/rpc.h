
#ifndef RPC_H

#define RPC_H

#define PORT 9090

#define BUFFER_SIZE 1024


typedef struct {
        char func_name[32];
        int args[2];
        int args_count;
} RpcRequest;

typedef struct {
        int success;
        int result;
        char error_message[128];
}RpcResponse ;
#endif RPC_H
