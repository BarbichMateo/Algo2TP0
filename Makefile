CCFLAGS= -Wall -ansi -pedantic 
CC= g++ 

all: tp0 clean
	

tp0: main.o cmdline.o 
	$(CC) $(CCFLAGS) -o tp0 main.o cmdline.o

main.o: main.cpp Array.h cmdline.h
	$(CC) $(CCFLAGS) -c main.cpp -o main.o 

cmdline.o: cmdline.cc cmdline.h
	$(CC) $(CCFLAGS) -c cmdline.cc -o cmdline.o 

#Array.o: Array.cpp Array.h
#	$(CC) $(CCFLAGS) -c Array.cpp -o Array.o 

#runtest.exe: runtest.cc
#	$(CC) $(CCFLAGS) -o runtest.exe runtest.cc
clean:
	$(RM) *.o 
