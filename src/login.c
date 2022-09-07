/*Client Login*/
//including header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "/home/ayushi/Cprog/sprint2/inc/proto.h"  

//assigning the password to admin for login
char pass[20] = MEET_PASSWORD;

int login_menu()
{
	int choice;//variable to get choice from the user
    system("clear");

    //Label for client
   	client:
		//display admin panel.
    	printf("\n\t\t\t****************\n");
    	printf("\n\t\t\t|    ---     !! Chat Room !!     ---        |\n");
    	printf("\n\n\t\t[1] Enter Chat Box\n\t\t[2] Exit\n\n\n\t\t Enter your choice:");

    	scanf("%d", &choice);//Enter the user choice:

    	//start switch_cases:
    	switch(choice)
    	{
			//To get enter chat room
    		case 1:
				return 1;
			//To exit from the program
    		case 2:
        		return 0;
        	default:
        		printf("Please enter the correct option!");
        	goto client;
    	}
    	
}

//Function to login 
int login()
{
    int attempt = 6;//number of attempts
	char client_room[10];//variable to store meeting room name
	
	label:
    	system("clear");

    	printf("\n\t\t\t->> Welcome to ChatRoom\n\t\t\t Enter your Meeting name: ");
    	scanf("%s", client_room);

		//If meeting name entered incorrect:
 		if(strcmp(client_room, MEETING_NAME) != 0)
    	{
        	
        	getchar();
        	printf("Wrong Meeting name!, please try again\n\n");
       	 	getchar();
        	goto label;
    	}
    	
    	//if username entered is correct
    	else
    	{
       		char user_pass[PASSWORD_LENGTH]; //variable to store password of meeting
    	
			label2:
		    	printf("\n\t\t\t>> Type password: ");
		    	scanf("%s", user_pass);

		    	//if password entered is incorrect.
		    	if(strcmp(user_pass, pass) != 0)
		    	{
		        	attempt--;
					//if password is entered incorrect for 5 times
		        	if(attempt == 0)
					{
				    	getchar();
				    	printf("\n\n");
				    
				    	perror("Too many wrong password ....");
				    	getchar();
				    	exit(EXIT_FAILURE);
					}
					printf("\n\t\t\t->>> Wrong password .Login attempt remaining %d", attempt);
		       	 	printf("\n\n");
		        	getchar();
		        	goto label2;
        		}//end of if
        		else
        		{
            		return login_menu;//redirect to the main account:
        		}
    	}//end of else
}
