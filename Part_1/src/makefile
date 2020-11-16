#
# In order to execute this "Makefile" just type "make"
#	Konstantina Nika, Nikitas Sakkas, Andreas Pappas,  
#      fall 2020-2021

OBJS	= project.o dot-C_files/structs.o dot-C_files/W_handler.o
SOURCE	= project.c dot-C_files/structs.c dot-C_files/W_handler.c
HEADER	= headers/structs.h headers/W_handler.h
OUT	= project1
CC	 = gcc
FLAGS	 = -g -c #-Wall
LFLAGS	 = -ljson-c
# -g option enables debugging mode 
# -c flag generates object code for separate files


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)


# create/compile the individual files >>separately<<
project.o: project.c
	$(CC) $(FLAGS) project.c 

src/dot-C_files/structs.o: dot-C_files/structs.c
	$(CC) $(FLAGS) dot-C_files/structs.c 

src/dot-C_files/W_handler.o: dot-C_files/W_handler.c
	$(CC) $(FLAGS) dot-C_files/W_handler.c 


# clean house
clean:
	rm -f $(OBJS) $(OUT)