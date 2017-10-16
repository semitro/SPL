#include "server/server.h"
#include "server/listener.h"
#include "server/client_handler.h"

void start_server(unsigned int port){
	set_client_handler(handle_client);
	start_listen(port);
}
