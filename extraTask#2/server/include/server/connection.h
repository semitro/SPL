#ifndef CONNECTION
#define CONNECTION
#include <netinet/in.h>
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct client{
	struct sockaddr_in addr;
	int fd;
};

#define MY_MSG_NOTIFY		0
#define MY_MSG_LIST			1
#define MY_MSG_EXEC_CODE	2
#define MY_MSG_BORDERS		3

struct message{
	char    type;
	size_t  len;
	void*   data;
};

#define MAX_BUFFER 512
ssize_t receive  (struct client const * const client, struct message       *	   message, size_t bytes);
ssize_t send_data(struct client const * const client, struct message const * const message);
ssize_t send_str (struct client const * const client, const  char*   const         str    );
#endif // CONNECTION

