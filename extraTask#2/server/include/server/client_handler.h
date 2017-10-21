#ifndef CLIENT_HANDLER
#define CLIENT_HANDLER

#include "server/connection.h"
#include "server/connection.h"
#include <stdio.h>
#include "list/list.h"
#include "server/server.h"
#include "string.h"
#include "list_keeper.h"

#define MAX_BUFFER_CODE 9044
// Вызывается листенером в новом потоке для каждого подключения
// (server.c указывает, что вызывается именно эта функция)
void handle_client(struct client client);

#endif // CLIENT_HANDLER

