CC=g++
CFLAGS= -c #-Wall -g

project_3: main_log_regr.o Logistic_Regr.o queue.o 
	$(CC) -pthread main_log_regr.o Logistic_Regr.o queue.o -o project_3 -lrt -lm

Logistic_Regr.o: source/Logistic_Regr.cpp include/Logistic_Regr.hpp include/queue.hpp
	$(CC) $(CFLAGS) source/Logistic_Regr.cpp

queue.o: source/queue.cpp include/queue.hpp include/Logistic_Regr.hpp
	$(CC) $(CFLAGS) source/queue.cpp
	
clean:
	rm *.o project_3
