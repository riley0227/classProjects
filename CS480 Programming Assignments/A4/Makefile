# CXX Make variable for compiler
CC=g++
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show all the necessary warning messages
# -g3         include extensive information for symbolic debugger e.g. gdb 
# -pthread    Use this flag to compile and link for thread support
CXXFLAGS=-std=c++11 -Wall -g3 -pthread

# Object files
OBJS = main.o producer.o consumer.o broker.o log.o

# Program name
PROGRAM = fooddelivery

# Default target
all: $(PROGRAM)

# Link the program with object files and specific flags if necessary
$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(CXXFLAGS)

# Compilation rules for individual object files
main.o: main.cpp Broker.h Producer.h Consumer.h log.h
	$(CC) $(CXXFLAGS) -c main.cpp -o main.o

producer.o: Producer.cpp Producer.h Broker.h fooddelivery.h
	$(CC) $(CXXFLAGS) -c Producer.cpp -o producer.o

consumer.o: Consumer.cpp Consumer.h Broker.h fooddelivery.h
	$(CC) $(CXXFLAGS) -c Consumer.cpp -o consumer.o

broker.o: Broker.cpp Broker.h
	$(CC) $(CXXFLAGS) -c Broker.cpp -o broker.o

log.o: log.cpp log.h
	$(CC) $(CXXFLAGS) -c log.cpp -o log.o

# Clean target to remove object files, program and editor backups
clean:
	rm -f $(OBJS) $(PROGRAM) *~
