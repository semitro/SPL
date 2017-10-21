#include "server/listener.h"


void(*handle_client_function)(struct client client);

void set_client_handler(void(*function)(struct client client) ){
		handle_client_function = function;
}

// Создание нового потока требует функци с такой сигнатурой
void* thread_work(void* arg){
        handle_client_function( *((struct client*)(arg)) );
        return NULL;
}

void start_listen(unsigned int port){
	int main_socket;
	struct sockaddr_in server_address;

        main_socket = socket(AF_INET, SOCK_STREAM,0);

	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);

	// Назначение порта для сервера
        if(0!= bind(main_socket,(struct sockaddr*)&server_address,sizeof server_address)){
		fprintf(stderr,"%s","Не удалось привязать адрес к сокету.");
		close(main_socket);
                _exit(1);
	}

	if(0!=listen(main_socket,MAX_CONNECTION))
	{
	   fprintf(stderr,"%s","Не удалось начать прослушку сервера.");
	   close(main_socket);
           _exit(2);
	}
	printf("The server is run on port %d\nWaiting for clients..\n", port);

	while (1) {
		// Для приходящего клиента
		struct client new_client;
		size_t new_addr_size = sizeof new_client.addr;
		new_client.fd =
		accept(main_socket,(struct sockaddr*)&new_client.addr, (socklen_t*)&new_addr_size);

		printf("Подключился новый клиент: %d\n", (int)new_client.addr.sin_addr.s_addr);

		pthread_t new_thread;
		pthread_create(&new_thread,NULL,thread_work,&new_client);
	}
	close(main_socket);
}
