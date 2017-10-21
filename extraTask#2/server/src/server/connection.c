#include "server/connection.h"


ssize_t receive  (struct client const * const client, struct message* message, size_t bytes){
                return recv(client->fd,
			 message,
			 bytes,
			 0);


}


ssize_t send_data(struct client const * const client, struct message const * const message){
		sleep(1);

        return send(            client->fd,
                                message,
                                message->len + sizeof(*message) - sizeof(message->data),
                                MSG_NOSIGNAL);
}

ssize_t send_str(struct client const* const client, const char* const str){
	// - sizeof void*, потому что массив внутри и есть входящий массив char
	struct message * const msg = malloc(strlen(str) + sizeof(struct message) - sizeof(void*));
	memset(msg,0,sizeof msg);
	msg->len  = strlen(str);
	msg->type = MY_MSG_NOTIFY;
	// now the structure is like an array with additional attributes
	// like len and type
	msg->data = &(msg->data);
	strcpy((char*)msg->data,str);
        ssize_t res = send_data(client,msg);

	free(msg);

        return res;
}
