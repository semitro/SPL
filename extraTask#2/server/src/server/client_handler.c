#include "server/client_handler.h"
#include <sys/mman.h>
#include <errno.h>

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

	free(msg);
}

void handle_client(struct client client){
	send_str(&client,"Welcome to object-popject servero,"
					 " senioro!");
	send_list(&client, get_list());

	struct message * msg = malloc(list_length(list)*sizeof(list_content)
								  + sizeof(*msg) - sizeof(msg->data));

	send_str(&client,"Select the borders");
	msg->type = MY_MSG_BORDERS;
	send_data(&client,msg);
	receive(&client,msg,MAX_BUFFER);
	printf("\nThe client #%d prepared bordes (%d,%d)\n",client.fd,*(int*)&msg->data,((int*)&msg->data)[1]);
	msg->type = MY_MSG_EXEC_CODE;
	msg->len=0;
	send_data(&client,msg);
	free(msg);


	// we need to get aligned by page-size memory to execute this shit
	msg  = mmap(NULL, MAX_BUFFER_CODE,
				PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	//
	printf("Receive %d bytes\n ", receive(&client,msg,MAX_BUFFER_CODE));

	printf("The client #%d sended %d bytes of an elf-file\n", client.fd, msg->len);

	apply_elf64_on_list(&msg->data,0,15);
	print_list(get_list());
}


