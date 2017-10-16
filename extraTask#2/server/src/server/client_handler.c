#include "server/client_handler.h"
#include "server/connection.h"
#include <stdio.h>

void handle_client(struct client client){
    struct message msg;
    msg.type = 42;
    msg.data = "Welcome to object-popject server!";
    msg.len  = 35;
    send_data(&client,&msg);
}
