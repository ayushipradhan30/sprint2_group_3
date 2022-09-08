//start file
#ifndef __PROTO_H__//allows for conditional compilation i.e. its the first file to be compiled
#define __PROTO_H__

/*For macros, use ALL_CAPS seperated by underscore*/
#define MINIMUM_USERNAME 2//minimum length of username
#define LENGTH_NAME 31//maximum username length
#define LENGTH_MSG 101//receiver message length
#define LENGTH_SEND 201//sender message length
#define IP_ADDRESS 16//length of IP address
#define MAX_CLIENTS 5//maximum number of clients
#define PORT 8888//port number
#define IP "127.0.0.1"//IP address
#define SEND_SUCCESS 2//message sent successfully
#define MEETING_NAME "group3"//Meeting name
#define MEET_PASSWORD "abc"//password for client
#define PASSWORD_LENGTH 6//length of passoword
#define STRING_OVERWRITE() (printf("\r%s", "> ") fflush(stdout));//function macro to print > symbol
#define USERNAME_SERVER "server"//username of server
#define PASSWORD_SERVER "123"//password of server

/*Function declaration*/
void str_trim_lf (char*, int);
#endif // PROTO
