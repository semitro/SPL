#include "server/client_handler.h"
#include "server/connection.h"
#include <stdio.h>
#include "list/list.h"
#include "server/server.h"
#include "string.h"

void send_list(struct client *client, list_node* list){

    struct message msg;
    msg.type = MY_MSG_LIST;
    msg.len = list_length(list)*sizeof(list_content);
	msg.data = malloc(msg.len);
    // Лист нужно преобразовать в массив-буфер
	list_content * i = msg.data;
    while(list){
        *i++ = list->value;
        list = list->next;
    }
    send_data(client,&msg);
	free(msg.data);
}

void handle_client(struct client client){
	struct message *msg = malloc(64);
	send_str(&client,"Welcome to object-popject servero, senioro!");
    sleep(5);
//    msg.data = "Current list:\0";
//    msg.len  = sizeof (msg->data) / sizeof(char);
    send_data(&client,msg);
    sleep(5);
    send_list(&client, get_list());
}


