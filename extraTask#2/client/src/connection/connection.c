#include "connection/connection.h"
#include <stdio.h>

int network_socket;
struct sockaddr_in server_address;

bool connect_to(char * const host, int port){
	//0 means default protocol, tcp
	network_socket = socket(AF_INET, SOCK_STREAM,0);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	inet_aton(host,&server_address.sin_addr);

	if(0!= connect(
					network_socket,
					(struct sockaddr* )&server_address,
					sizeof(server_address)
                                ))
	{
		return false;
	}
	else
		return true;
}


ssize_t send_data(const void * const data, size_t len){
	return send(network_socket,data,len,MSG_NOSIGNAL);
}

ssize_t receive_data(void *buf, size_t buf_size){
	return recv(network_socket,buf,buf_size,0);
}
