#ifndef SERVER_H
#define SERVER_H

#include "listener.h"
#include "connection.h"
#include "list/list.h"

// Точка входа в модуль для внешней среды
void start_server(unsigned int port);

list_node* get_list();
#endif // SERVER_H

