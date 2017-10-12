//
// Created by semitro on 12.10.17.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <elf.h>
#include "list"

// we can use gf to move inside .h file
// to return, use ctr+o

int main(int argc, char** argv){
    int fd = socket(AF_INET, SOCK_STEAM,0);
    if(fd == -1){
        puts("Не удалось создать сокет");
        return 0;
    }

    struct sockaddr_in server_address;
    Elf64Shdr s;
    xui d;

    return 0;
}
