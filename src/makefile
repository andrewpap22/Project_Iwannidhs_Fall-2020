#
# In order to execute this "Makefile" just type "make"
#	Konstantina Nika, Nikitas Sakkas, Andreas Pappas,  
#      fall 2020-2021

OBJS	= project.o dot-C_files/structs.o dot-C_files/W_handler.o dot-C_files/json_parser.o
SOURCE	= project.c dot-C_files/structs.c dot-C_files/W_handler.c dot-C_files/json_parser.c 
HEADER	= headers/structs.h headers/W_handler.h headers/json_parser.h headers/includes_for_parser.h
OUT	= project1
CC	 = gcc
FLAGS	 = -g -c -Wall
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

src/dot-C_files/json_parser.o: dot-C_files/json_parser.c
	$(CC) $(FLAGS) dot-C_files/json_parser.c 


# clean house
clean:
	rm -f $(OBJS) $(OUT)