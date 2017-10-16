#ifndef CLIENT_HANDLER
#define CLIENT_HANDLER

#include "server/connection.h"

// Вызывается листенером в новом потоке для каждого подключения
// (server.c указывает, что вызывается именно эта функция)
void handle_client(struct client client);

#endif // CLIENT_HANDLER

