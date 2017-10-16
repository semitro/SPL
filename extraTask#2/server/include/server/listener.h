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

#include "connection.h"

#define MAX_CONNECTION 128


void start_listen(unsigned int port);
// То, что будет вызываться при каждом подключении
void set_client_handler( void(*function)(struct client client) );

#endif // LISTENER_H

