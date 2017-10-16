#ifndef LISTENER_H
#define LISTENER_H

#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <arpa/inet.h>

#define MAX_CONNECTION 128

void start(unsigned int port);

#endif // LISTENER_H

