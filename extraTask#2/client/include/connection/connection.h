#ifndef CONNECTION
#define CONNECTION

#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <arpa/inet.h>

#define MY_MSG_NOTIFY 0
#define MY_MSG_LIST   1

struct message{
	char    type;
	size_t  len;
	void*   data;
};

// host in ipv4
bool connect_to(char* const host, int    port);
// returns sended bytes. -1 if error.
ssize_t send_data(const void* const data, size_t len);
ssize_t receive_data(void* buf, size_t buf_size);
#endif // CONNECTION

