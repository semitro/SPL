#ifndef CONNECTION
#define CONNECTION
#include <netinet/in.h>

struct client{
	struct sockaddr_in addr;
	int fd;
};

#define MY_MSG_NOTIFY 0

struct message{
	char type;
	void* data;
	size_t len;
};

ssize_t receive  (struct client const * const client, struct message       * const message);
ssize_t send_data(struct client const * const client, struct message const * const message);

#endif // CONNECTION

