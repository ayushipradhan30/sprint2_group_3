/*creating TCP socket for client side and using various system calls like send(), connect(),  close() to connect to the server */
 
//including header files for this particular code
#include <../inc/proto.h>
#include <../inc/client.h>

// Global variables
volatile sig_atomic_t flag = 0;//flag for client availability
int sockfd = 0;//socket number
char username[LENGTH_NAME] = {};//username

/*Function names are lower_case. Opening braces on the next line*/

//to remove extra whitespaces 
void str_trim_lf (char* arr, int length) 
{
    int i;
    for (i = 0; i < length; i++) 
    {
        if (arr[i] == '\n') 
        {
            arr[i] = '\0';
            break;
        }
    }
}  


/*Exit function*/
void catch_ctrl_c_and_exit(int sig) 
{
    flag = 1;
}

/*Functionn for receiving message*/
void recv_msg_handler() 
{
    char receiveMessage[LENGTH_SEND] = {0};//receive message
    while (1) {
        int receive = recv(sockfd, receiveMessage, LENGTH_SEND, 0);//receive function returns integer value
        
        /*checking if message received successfully*/
        if (receive > 0) {
            printf("\r%s\n", receiveMessage);
            printf("\r%s", "> ");
            fflush(stdout);
        } else if (receive == 0) {
            break;
        } else { 
            perror("Fatal Error.\n");
        }//end of else
    }//end of while
}

/*Function for sending message*/
void send_msg_handler() 
{
    char message[LENGTH_MSG] = {0};
    
    /*checking if message sent successfully*/
    while (1) 
    {
       printf("\r%s", "> ");
       fflush(stdout);
        while (fgets(message, LENGTH_MSG, stdin) != NULL) 
        {
            str_trim_lf(message, LENGTH_MSG);
            if (strlen(message) == 0) {
                printf("\r%s", "> ");
                fflush(stdout);
            } else {
                break;
            }
        }//end of while
        send(sockfd, message, LENGTH_MSG, 0);
        if (strcmp(message, "exit") == 0) {
            break;
        }//end of if
    }//end of while
    catch_ctrl_c_and_exit(EXIT_SUCCESS);
}

/* Main function for client*/
int main()
{   	
	//Thread declarations
	pthread_t recv_msg_thread;
	pthread_t send_msg_thread;
	
	/*Login function*/
    if(!login()){
        	printf("Successfully Logout\n\n");
   	} 
	
	//if the login is successful
    else{
		signal(SIGINT, catch_ctrl_c_and_exit); //sigint to stop the current process and return to its main loop 

		// Naming
		printf("Please enter your name: ");
		getchar(); 
		if (fgets(username, LENGTH_NAME, stdin) != NULL) 
		{
		    str_trim_lf(username, LENGTH_NAME);
		}
		if (strlen(username) < MINIMUM_USERNAME || strlen(username) >= LENGTH_NAME-1) 
		{
		    printf("\nName must be more than one and less than thirty characters.\n");
		    exit(EXIT_FAILURE);
		}
		//Creating socket for client side
		sockfd = socket(AF_INET , SOCK_STREAM , 0);//
		
		//Checking condition for socket creation
		if (sockfd < 0)
		{
		    perror("Fail to create a socket.");  //error condition
		    exit(EXIT_FAILURE);
		}

		// Socket information
		struct sockaddr_in server_info, client_info; // declaring a sockaddr_in in structure.
		int ServerAddrLen = sizeof(server_info);
		int ClientAddrLen = sizeof(client_info);
		
		//memset() used to fill block of memory with a particular value    
		//function fills the first ServerAddrLen(size) bytes of the memory area pointed to by server_info with the 0.
		memset(&server_info, 0, ServerAddrLen); 
		memset(&client_info, 0, ClientAddrLen);
		
		//server information
		server_info.sin_family = PF_INET;  
		server_info.sin_addr.s_addr = inet_addr(IP); 
		server_info.sin_port = htons(PORT); 

		// Connect to Server
		int err = connect(sockfd, (struct sockaddr *)&server_info, ServerAddrLen);
		if (err < 0) 
		{
		    perror("Connection to Server error!\n");
		    exit(EXIT_FAILURE);
		}
		
		//Functions used to get names of current client and server
		getsockname(sockfd, (struct sockaddr*) &client_info, (socklen_t*) &ClientAddrLen);
		getpeername(sockfd, (struct sockaddr*) &server_info, (socklen_t*) &ServerAddrLen);
		
		//Printing messages to inform user if connection established
		printf("Connect to Server: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
		printf("You are: %s:%d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

		//condition to check if message sent successfully
		if(send(sockfd, username, LENGTH_NAME, 0) < 0)
		{
			perror("Send function failed.\n");
			exit(EXIT_FAILURE);
		}
		
		//creating a thread for sending message
		if (pthread_create(&send_msg_thread, NULL, (void *) send_msg_handler, NULL) != 0) 
		{
		    perror("Create pthread error!\n");
		   	pthread_exit(&send_msg_thread);
		    exit(EXIT_FAILURE);
		}
		
		//creating a thread for receiving message
		if (pthread_create(&recv_msg_thread, NULL, (void *) recv_msg_handler, NULL) != 0) 
		{
		    perror("Create pthread error!\n");
		    pthread_exit(&recv_msg_thread);
		    exit(EXIT_FAILURE);
		}
		
		/*condition to check if the user exist*/
		while (1) 
		{
		    if(flag) 
		    {
		        printf("\nBye\n");
		        printf("Successfully Logout\n\n");
		        break;
		    }
		}//end of while
		close(sockfd);//closing socket 
	}//end of else
	return 0;
}
