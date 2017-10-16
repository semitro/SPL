#ifndef CONNECTION
#define CONNECTION
#include <netinet/in.h>

struct client{
	struct sockaddr_in addr;
	int fd;
};

#define MY_MSG_NOTIFY 0
#define MY_MSG_LIST   1

struct message{
	char    type;
	size_t  len;
	void*   data;
};

ssize_t receive  (struct client const * const client, struct message       * const message);
ssize_t send_data(struct client const * const client, struct message const * const message);
ssize_t send_str (struct client const * const client, const  char*   const         str    );
#endif // CONNECTION

