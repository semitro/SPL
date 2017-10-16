#include <stdio.h>
#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <string.h>
#include "server/listener.h"

void start(unsigned int port){
	int main_socket;
	struct sockaddr_in server_address;

	main_socket = socket(AF_INET, SOCK_STREAM,0);

	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	// Назначение порта для сервера
	if(0!= bind(main_socket,&server_address,sizeof server_address)){
		fprintf(stderr,"%s","Не удалось привязать адрес к сокету.");
		close(main_socket);
		exit(1);
	}

	if(0!=listen(main_socket,MAX_CONNECTION))
	{
	   fprintf(stderr,"%s","Не удалось начать прослушку сервера.");
	   close(main_socket);
	   exit(2);
	}

	struct sockaddr_in new_client_addr;
	size_t new_addr_size = sizeof new_client_addr;
	printf("Подключился новый клиент: %d\n",
				  accept(main_socket,&new_client_addr, &new_addr_size));

	close(main_socket);
	close(new_client_addr);
}

