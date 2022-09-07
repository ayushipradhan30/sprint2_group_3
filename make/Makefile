#makefile to compile all the files
INC = /home/ayushi/Cprog/sprint2/inc
BIN = /home/ayushi/Cprog/sprint2/bin
SRC =/home/ayushi/Cprog/sprint2/src
OBJ = /home/ayushi/Cprog/sprint2/obj
DATA = /home/ayushi/Cprog/sprint2/data

LFLAGS = -o
GCC = gcc
CFLAGS =  -c -g
IFLAGS = -I $(INC)

all: $(BIN)/client $(BIN)/server

$(OBJ)/client.o : $(SRC)/login.c $(SRC)/client.c
	$(GCC) $(CFLAGS) $(SRC)/login.c $(SRC)/client.c $(IFLAGS) 
	mv *.o /home/ayushi/Cprog/sprint2/obj

$(OBJ)/login.o : $(SRC)/login.c
	$(GCC) $(CFLAGS) $(SRC)/login.c $(IFLAGS) 
	mv *.o /home/ayushi/Cprog/sprint2/obj

$(BIN)/client : $(OBJ)/client.o $(OBJ)/login.o $(OBJ)/string.o 
	$(GCC) $(OBJ)/string.o $(OBJ)/client.o $(OBJ)/login.o $(LFLAGS) $(BIN)/client

$(OBJ)/server.o : $(SRC)/server.c 
	$(GCC) $(CFLAGS) $(SRC)/server.c $(IFLAGS)
	mv *.o /home/ayushi/Cprog/sprint2/obj

$(BIN)/server : $(OBJ)/server.o $(OBJ)/string.o  
	$(GCC) $(OBJ)/string.o $(OBJ)/server.o $(LFLAGS) $(BIN)/server
	
$(OBJ)/string.o : $(SRC)/string.c 
	$(GCC) $(CFLAGS) $(SRC)/string.c $(IFLAGS)
	mv *.o /home/ayushi/Cprog/sprint2/obj
