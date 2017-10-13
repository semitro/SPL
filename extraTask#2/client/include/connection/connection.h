#ifndef CONNECTION
#define CONNECTION

#include <netinet/in.h>
#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <arpa/inet.h>

// host in ipv4
bool connect_to(char* const host, int    port);
// returns sended bytes. -1 if error.
ssize_t send_data(const void* const data, size_t len);
ssize_t receive_data(void* buf, size_t buf_size);
#endif // CONNECTION

