#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include "list/list.h"
#include "list/list_functions.h"
#include "list/list_serialize.h"
#include "connection/connection.h"

#define BUFF_SIZE 512


void handle_msg(struct message* msg_in);

int main(int argc, char** argv){
	if(argc != 3){
		puts("Usage: host port");
		exit(0);
	}
	if(!connect_to(argv[1],atoi(argv[2]))){
		printf("Не приконнектились");
		exit(1);
	}

	struct message *msg_in = malloc(BUFF_SIZE);
	while(1){
                memset     (msg_in,0,BUFF_SIZE);
                printf     ("Receive %d bytes from the server.\n",(int)receive_data(msg_in,BUFF_SIZE));
                handle_msg (msg_in);
	}
        free(msg_in);
	return 0;
}

void print_list(list_content v){
	printf("%d->",v);
}

list_node* list_take(const struct message* const msg);

void handle_msg(struct message* msg_in){
	printf("Type: %d\n",msg_in->type);
	if(MY_MSG_NOTIFY == msg_in->type) printf("Server: %s \n",(char*)&msg_in->data);
	if(MY_MSG_LIST   == msg_in->type){
                puts("Подкатил лист");
				list_for_each(list_take(msg_in),print_list);
                puts("");
	}
}

list_node* list_take(const struct message* const msg){
	list_node* l = NULL;
	size_t size = msg->len/sizeof(list_content);
	size_t i = 0;

	while(i < size)
		if(l)
		 list_add_back  ((list_content) ((list_content*)&msg->data)[i++],&l);
			else
				 l = list_create((list_content) ((list_content*)&msg->data)[i++]);

    return l;
}
