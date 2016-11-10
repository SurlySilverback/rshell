objects = main.o and.o line.o or.o parser.o tree_construct_record.o \
          token_interpreter.o tree_record_updater.o process.o

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
parser.o : tree_construct_record.h token_interpreter.h \ 
           tree_record_updater.h process.h
process.o : command.h
tree_construct_record.o : 
token_interpreter.o : tree_construct_record.h
tree_record_updater.o : tree_construct_record.h token_interpreter.h \
                        process.h and.h or.h

.PHONY : clean
clean :
	-rm rshell $(objects)