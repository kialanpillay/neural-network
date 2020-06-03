CC=g++         
CCFLAGS= -std=c++11 -Wall -g -fsanitize=address -fno-omit-frame-pointer

driver: driver.o neural_network.o data.o perceptron.o input.o
	$(CC) $(CCFLAGS) driver.o neural_network.o data.o perceptron.o input.o -o driver

driver.o: driver.cpp
	$(CC) $(CCFLAGS) -c driver.cpp	

neural_network.o: neural_network.cpp neural_network.h
	$(CC) $(CCFLAGS) -c neural_network.cpp

data.o: data.cpp data.h
	$(CC) $(CCFLAGS) -c data.cpp

input.o: input.cpp input.h
	$(CC) $(CCFLAGS) -c input.cpp

perceptron.o: perceptron.cpp perceptron.h
	$(CC) $(CCFLAGS) -c perceptron.cpp


clean:
	@rm -f *.o && rm -f driver
   
run:
	@./driver

