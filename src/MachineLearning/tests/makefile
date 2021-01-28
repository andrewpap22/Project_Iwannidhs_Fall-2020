CC=g++
CFLAGS= -c #-Wall -g

ML_test: ML_test.o
	$(CC) -pthread ML_test.o ../Logistic_Regr.o ../queue.o -o ML_test -lrt -lm -lgtest -lgtest_main 

# Logistic_Regr.o: ../source/Logistic_Regr.cpp ../include/Logistic_Regr.hpp ../include/queue.hpp
# 	$(CC) $(CFLAGS) ../source/Logistic_Regr.cpp

# queue.o: ../source/queue.cpp ../include/queue.hpp ../include/Logistic_Regr.hpp
# 	$(CC) $(CFLAGS) ../source/queue.cpp
	
clean:
	rm *.o ML_test
