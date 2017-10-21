#include "server/client_handler.h"
#include "server/connection.h"
#include <stdio.h>
#include "list/list.h"
#include "server/server.h"
#include "string.h"

void send_list(struct client *client, list_node* list){

	struct message * msg = malloc(list_length(list)*sizeof(list_content)
									 + sizeof(*msg) - sizeof(msg->data));
	memset(msg,0,8*sizeof msg);
	msg->type = MY_MSG_LIST;
	msg->len  = list_length(list)*sizeof(list_content);
	msg->data = &(msg->data);

    // Лист нужно преобразовать в массив-буфер
	list_content *i = (list_content*)msg->data;
    while(list){
        *i++ = list->value;
        list = list->next;
    }
	send_str(client,"Catch the list!");
	send_data(client,msg);
	send_str(client,"Select the borders");
	msg->type = MY_MSG_BORDERS;
	send_data(client,msg);
	printf("\n%d - receive\n",receive(client,msg));
				//int n = *(int*)(&msg->data);
                printf("%d %d\n",*(int*)&msg->data,((int*)&msg->data)[1]);

	free(msg);
}

void handle_client(struct client client){
	send_str(&client,"Welcome to object-popject servero,"
					 " senioro!");
    send_list(&client, get_list());

}


