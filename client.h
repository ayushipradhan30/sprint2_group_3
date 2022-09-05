//header file for client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>//includes collection of typedef symbols and structures.

#include <sys/socket.h>//includes socket length which is of an integer type

#include <netinet/in.h>//includes definations for IP family

#include <arpa/inet.h>
#include <pthread.h> //includes function declarations and mappings for thread interfaces and defines constants used by those functions.
#define LENGTH_NAME 31//username length
#define LENGTH_MSG 101//receiver message length
#define LENGTH_SEND 201//sender message length
#define IP_ADDRESS 16//length of IP address

#define PORT 8888//port number
#define IP "127.0.0.1"//IP address
#define MEETING_NAME "group3"//Meeting name

#define MEET_PASSWORD "abc"//password for client
#define PASSWORD_LENGTH 6//length of passoword

#define USERNAME_SERVER "server"//username of server
#define PASSWORD_SERVER "123"//password of server
//function declaration
int login(); 
void catch_ctrl_c_and_exit(int);/*Exit function*/
void recv_msg_handler();
void send_msg_handler();
