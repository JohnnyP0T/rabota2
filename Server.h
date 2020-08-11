  #pragma once
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <iostream>
#include <fstream>
using namespace std;
#define LBUF 128
#define LBUF2 20
#define LEN sizeof(struct sockaddr_in) 


class Server
{
    public:
    void StartServer();
    private:
    int CheckSum(char *msg);
};