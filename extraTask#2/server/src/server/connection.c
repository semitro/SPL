#include "server/connection.h"

ssize_t receive  (struct client const * const client, struct message * const message){

}

ssize_t send_data(struct client const * const client, struct message const * const message){
	return send(client->fd,message->data,message->len,MSG_NOSIGNAL);
}
