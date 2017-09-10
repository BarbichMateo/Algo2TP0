CCFLAGS= -Wall -ansi -pedantic 
CC= g++ 

all: tp0 clean
	

tp0: main.o cmdline.o utils.o
	$(CC) $(CCFLAGS) -o tp0 main.o cmdline.o utils.o

main.o: main.cpp Array.h cmdline.h utils.h
	$(CC) $(CCFLAGS) -c main.cpp -o main.o 

cmdline.o: cmdline.cc cmdline.h
	$(CC) $(CCFLAGS) -c cmdline.cc -o cmdline.o 

utils.o: utils.cpp utils.h
	$(CC) $(CCFLAGS) -c utils.cpp -o utils.o 

#runtest.exe: runtest.cc
#	$(CC) $(CCFLAGS) -o runtest.exe runtest.cc
clean:
	$(RM) *.o 
