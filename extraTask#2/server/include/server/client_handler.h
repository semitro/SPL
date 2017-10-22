#ifndef CLIENT_HANDLER
#define CLIENT_HANDLER

#include "server/connection.h"
#include "server/connection.h"
#include "list/list.h"
#include "server/server.h"
#include "string.h"
#include "list_keeper.h"

#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>

#define MAX_BUFFER_CODE 64000

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// Вызывается листенером в новом потоке для каждого подключения
// (server.c указывает, что вызывается именно эта функция)
void handle_client(struct client client);

#endif // CLIENT_HANDLER

