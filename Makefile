CC = g++

CFLAGS = -Wall -Werror -ansi -pedantic


all :
	mkdir -p ./bin
	$(CC) $(CFLAGS) ./src/main.cpp -o ./bin/rshell

main :
	$(CC) $(CFLAGS) ./src/main.cpp
	
Command :
	$(CC) $(CFLAGS) ./src/Command.h

And :
	$(CC) $(CFLAGS) ./src/And.h

Or :
	$(CC) $(CFLAGS) ./src/Or.h

Line :
	$(CC) $(CFLAGS) ./src/Line.h
	
Parser :
	$(CC) $(CFLAGS) ./src/Parser.h

Token_Interpreter :
	$(CC) $(CFLAGS) ./src/Token_Interpreter.h
	
Tree_Construct_Record :
	$(CC) $(CFLAGS) ./src/Tree_Construct_Record.h
	
Tree_Record_Updater :
	$(CC) $(CFLAGS) ./src/Tree_Record_Updater.h

Process :
	$(CC) $(CFLAGS) ./src/Process.h

TestProcess :
	$(CC) $(CFLAGS) ./src/TestProcess.h



.PHONY : clean
clean :
	rm -rf ./bin