//header file for server
#ifndef __SERVER_H__
#define __SERVER_H__
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
#include <../inc/proto.h>

/*Function declaration*/
extern void client_handler(void *);  
extern void str_trim_lf (char*, int);
#endif // LIST
