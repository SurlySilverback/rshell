objects = main.o and.o line.o or.o parser.o
VPATH = src

all : $(objects)
	mkdir -p bin
	cc -Wall -Werror -ansi -pedantic all $(objects)
	
rshell : $(objects)
	mkdir -p bin
	cc -Wall -Werror -ansi -pedantic rshell $(objects)

main.o : command.h and.h or.h process.h
and.o : command.h
line.o : command.h
or.o : command.h
parser.o : #FIXME include the header files for parser here

.PHONY : clean
clean :
	-rm rshell $(objects)