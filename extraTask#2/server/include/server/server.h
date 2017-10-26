#ifndef SERVER_H
#define SERVER_H

#include "listener.h"
#include "connection.h"
#include "list/list.h"
#include "list/list_functions.h"
#include "list_keeper.h"
#include "server/listener.h"
#include "server/client_handler.h"
// Точка входа в модуль для внешней среды
void start_server(unsigned int port);

list_node* get_list();
#endif // SERVER_H

