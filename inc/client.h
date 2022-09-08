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
#include <pthread.h> //includes function declarations and mappings for thread interfaces 
#define MINIMUM_USERNAME 2//minimum length of username
//function declaration
extern int login(); 
extern void catch_ctrl_c_and_exit(int);/*Exit function*/
extern void recv_msg_handler();
extern void send_msg_handler();
