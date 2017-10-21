#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list/list.h"
#include "list/list_functions.h"
#include "list/list_serialize.h"
#include "connection/connection.h"
#include "exec_code.h"

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
				memset       (msg_in,0,BUFF_SIZE);
				receive_data (msg_in,BUFF_SIZE);
				handle_msg   (msg_in);
	}
        free(msg_in);
	return 0;
}

void print_list(list_content v){
	printf("%d->",v);
}

list_node* list_take(const struct message* const msg);
void handle_user_input(char type){
	printf("You: ");
	// Готовим сообщение для отправки
	struct message* msg_out;
	switch(type){
		case MY_MSG_BORDERS:
			msg_out = malloc(sizeof *msg_out + sizeof(int)*2 - sizeof(void*));
			msg_out->type = MY_MSG_BORDERS;
			msg_out->len = sizeof(int)*2; // len - длина data в байтах
			// Считываем две интушки в массив даты
			msg_out->data = &msg_out->data;
			int n1,n2;
			scanf("%d %d",  &n1, &n2);
			*((int*)msg_out->data)    = n1;
			((int*)&msg_out->data)[1] = n2;
			send_data(msg_out, sizeof(*msg_out) + sizeof(int)*2 - sizeof(void*));

			free(msg_out);
			break;

		case MY_MSG_EXEC_CODE: //file-nile
			printf("Server's waiting for you command\nEnter the file-name to transfer its code\n");
			char* file_name = malloc(512);
			scanf("%s",file_name);
			msg_out = malloc(MAX_BUFFER_LOAD);

			while(! (msg_out->len = load_from_file(file_name,&msg_out->data))){
							puts("Enter the name of existing file:");
							scanf("%s",file_name);
						}

			printf("Sended %d bytes of code",
                               send_data(msg_out,sizeof(*msg_out)+sizeof(msg_out->len)-sizeof(void*)));
		free(msg_out);
			break;
	}

}

void handle_msg(struct message* msg_in){
    list_node *l;
    switch(msg_in->type){
	case MY_MSG_NOTIFY:
		printf("Server: %s \n",(char*)&msg_in->data);
		break;

	case MY_MSG_LIST:
		l =  list_take(msg_in);
		list_for_each(l,print_list);
		list_free(&l);
		puts("X");
		break;
	case MY_MSG_EXEC_CODE:
	case MY_MSG_BORDERS:
		handle_user_input(msg_in->type);
		break;
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
