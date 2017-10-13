#include <sys/socket.h>
#include <stdlib.h>

#include "connection/connection.h"
int main(int argc, char** argv){
	if(argc != 3){
		puts("Usage: host port");
		exit(0);
	}
	if(!connect_to(argv[1],atoi(argv[2]))){
		printf("Не приконнектились");
		exit(1);
	}

	char data[17] = "123456ConnectionSucces!\n";
	receive_data(data,6);
	send_data(data, sizeof(data));
	return 0;
}
