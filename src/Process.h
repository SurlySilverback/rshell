#ifndef PROCESS_H
#define PROCESS_H

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "Command.h"

class Process: public Command {
  private:
    char* exec_name;
    char** args;

  public:
    Process(char* exec_name, char** args) 
    { 
      this-> exec_name = exec_name; 
      this-> args = args;
    }

    bool execute() 
    {
      //prepend exec_name to args, per execvp API
      this->args = prepend_char_pointer_array();
		
      pid_t pid = fork();		
 
      if ( pid == -1 )
          perror("fork");
      
      if ( pid == 0 ) 
      {
          //child     
          if ( execvp( this->exec_name, this->args ) == -1 )
              perror("exec");
        
          else
            return true;
      }   
      
      if ( pid > 0 )
      {
          //parent
          wait(0);
     }
      
      return true;
    }

    char** prepend_char_pointer_array() {
      unsigned array_size = 0;
      for(unsigned i = 0; this->args[i] != NULL; i++)
	array_size++;
     
      char** updated_array = new char*[array_size + 1];
      updated_array[0] = this->exec_name;

      //copy original array
      for (unsigned i = 1; this->args[i - 1] != NULL; i++) 
        updated_array[i] = this->args[i - 1];

      delete [](this->args);
      return updated_array;
    }
};
	
#endif
