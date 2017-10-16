#include <sys/socket.h>
#include <stdlib.h>
#define BUFF_SIZE 512
#include "connection/connection.h"

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

	struct message msg_in;
	msg_in.data = malloc(BUFF_SIZE);
	while(1){
		printf("Receive %d bytes from the server.\n",receive_data(&msg_in,BUFF_SIZE));
		handle_msg  (&msg_in);
	}
	free(msg_in.data);
	return 0;
}

void handle_msg(struct message* msg_in){
	printf("Type: %d\n",msg_in->type);
	if(MY_MSG_NOTIFY == msg_in->type) printf("Server: %s \n",(char*)&msg_in->data);
	if(MY_MSG_LIST   == msg_in->type) printf("Подкатил лист");
}
