/*creating TCP socket for server side and using various system calls like bind(), listen(), recv(), send(), close() to accept incoming connections from the client side and communicating with multiple clients by using TCP protocol. */
 
//including header files for this particular code
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
#include "/home/ayushi/Cprog/sprint2/inc/server.h"
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
// Global variables
int server_sockfd = 0, client_sockfd = 0;
ClientList *root, *now;

/*Function names are lower_case. Opening braces on the next line*/

//Exit function
void catch_ctrl_c_and_exit(int sig) 
{
    ClientList *tmp;
    while (root != NULL) {
        printf("\nClose socketfd: %d\n", root->data);
        close(root->data); // close all socket include server_sockfd
        tmp = root;
        root = root->link;
        free(tmp);
    }
    printf("Bye\n");
    exit(EXIT_SUCCESS);
}

//sending message to all clients
void send_to_all_clients(ClientList *np, char tmp_buffer[]) 
{
    ClientList *tmp = root->link;
    while (tmp != NULL) 
    {
        if (np->data != tmp->data) // all clients except itself.
        { 
            printf("Send to sockfd %d: \"%s\" \n", tmp->data, tmp_buffer);
            send(tmp->data, tmp_buffer, LENGTH_SEND, 0);
        }
        tmp = tmp->link;
    }
}

//handling client data
void client_handler(void *p_client) 
{
    int leave_flag = 0;
    char username[LENGTH_NAME] = {};
    char recv_buffer[LENGTH_MSG] = {};
    char send_buffer[LENGTH_SEND] = {};
    ClientList *np = (ClientList *)p_client;

    //Validating Name
    
    /*else and else if comes after the previous closing brace and not on
	 *the next line.*/
    if (recv(np->data, username, LENGTH_NAME, 0) <= 0 || strlen(username) < 2 || strlen(username) >= LENGTH_NAME-1) 
    {
        printf("%s didn't input name.\n", np->ip);
        leave_flag = 1;
    } else {
        strncpy(np->name, username, LENGTH_NAME);
        printf("%s(%s)(%d) join the chatroom.\n", np->name, np->ip, np->data);
        sprintf(send_buffer, "%s(%s) join the chatroom.", np->name, np->ip);
        send_to_all_clients(np, send_buffer);
    }

    // Conversation
    while (1) 
    {
        if (leave_flag) 
        {
            break;
        }
        int receive = recv(np->data, recv_buffer, LENGTH_MSG, 0);
        
        if (receive > 0) 
        {
            if (strlen(recv_buffer) == 0) 
            {
                continue;
            }
            sprintf(send_buffer, "%s：%s from %s", np->name, recv_buffer, np->ip);
        } else if (receive == 0 || strcmp(recv_buffer, "exit") == 0) 
        {
            printf("%s(%s)(%d) leave the chatroom.\n", np->name, np->ip, np->data);
            sprintf(send_buffer, "%s(%s) leave the chatroom.", np->name, np->ip);
            leave_flag = 1;
        } else 
        {
            perror("Fatal Error: -1\n");
            leave_flag = 1;
        }
        send_to_all_clients(np, send_buffer);
    }

    // Remove Node
    close(np->data);
    if (np == now)// remove an edge node 
    { 
        now = np->prev;
        now->link = NULL;
    } else // remove a middle node
    {
        np->prev->link = np->link;
        np->link->prev = np->prev;
    }
    free(np);
}

/* Main function to create a TCP socket , and also creating system calls like bind() and listen() and accept connection from the client*/
int main()
{
    char username[LENGTH_NAME]; //username
    char password[PASSWORD_LENGTH]; //password
    
    /*Signal to invoke the exit function*/
    signal(SIGINT, catch_ctrl_c_and_exit); //sigint to stop the current process and return to its main loop 
 
 	/*Server Login */
    printf("Enter your username: "); 
    scanf("%s",username); 
 
    printf("Enter your password: "); 
    scanf("%s",password); 
 
    if(strcmp(username,USERNAME_SERVER)==0){ 
    	if(strcmp(password,PASSWORD_SERVER)==0){ 
 
        	printf("\nWelcome.Login Success!\n"); 
        }else{ 
    		perror("\nwrong password\n");
    		exit(EXIT_FAILURE); 
		} 
    }else{ 
    	perror("\nUser doesn't exist\n"); 
    	exit(EXIT_FAILURE);
	} 
 
 	//Creating socket for server side
    server_sockfd = socket(AF_INET , SOCK_STREAM , 0);
    
    //Checking condition for socket creation
    if (server_sockfd == -1)   
    {
        perror("Fail to create a socket.");  //error condition
        exit(EXIT_FAILURE);
    }

    //IP Address 
    struct sockaddr_in server_info, client_info; // declaring a sockaddr_in in structure
    
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
	
	//memset() used to fill block of memory with a particular value
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);
    
    //Socket information
    server_info.sin_family = PF_INET; //info to which family it belongs (IPV4)
    server_info.sin_addr.s_addr = INADDR_ANY;  //address creation
    server_info.sin_port = htons(PORT);  //port address creation

    //Bind and Listen system calls
    bind(server_sockfd, (struct sockaddr *)&server_info, s_addrlen);
    listen(server_sockfd, MAX_CLIENTS);

 	//To print server IP
    getsockname(server_sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);
       
    printf("Start Server on: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));

    // Initial linked list for clients
    root = newNode(server_sockfd, inet_ntoa(server_info.sin_addr));
    now = root;

    while (1) 
    {
        client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
		
        // Print Client IP
        getpeername(client_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
        printf("Client %s:%d come in.\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

        // Append linked list for clients
        ClientList *c = newNode(client_sockfd, inet_ntoa(client_info.sin_addr));
        c->prev = now;
        now->link = c;
        now = c;

		//creating a thread for client handler
  		pthread_t id;   //defining a thread variable called id 
 
		//condition to check if the thread created for client_handler 
  		if (pthread_create(&id, NULL, (void *)client_handler, (void *)c) != 0) 
  		{
            perror("Create pthread error!\n");
            exit(EXIT_FAILURE);
        }
    }
   return 0;
}
