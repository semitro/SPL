#ifndef LISTENER_H
#define LISTENER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_CONNECTION 128
struct client{
	struct sockaddr_in addr;
	int fd;
};

void start(unsigned int port);
void set_client_handler( void(*function)(struct client client) );
#endif // LISTENER_H

