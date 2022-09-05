//header file for server
#ifndef _SERVER_H_
#define _SERVER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "/home/ayushi/Cprog/sprint2/inc/proto.h"
#define MAX_CLIENTS 5//maximum number of clients

//structure for client node, its a doubly linked list
typedef struct ClientNode 
{
    int data;//store data of socket
    struct ClientNode* prev;//link to prevoius node
    struct ClientNode* link;//link to next node
    char ip[IP_ADDRESS];//ip address
    char name[LENGTH_NAME];//username
} ClientList;

//node creation for client list
ClientList *newNode(int sockfd, char* ip) 
{
    ClientList *np = (ClientList *)malloc( sizeof(ClientList) );//create new node np
    np->data = sockfd;//store socket information
    np->prev = NULL;
    np->link = NULL;
    strncpy(np->ip, ip, IP_ADDRESS);//copies the IP to the node
    strncpy(np->name, "NULL", LENGTH_NAME);//copies name to the node
    return np;
}

#endif // LIST
