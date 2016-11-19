#ifndef PROCESS_H
#define PROCESS_H

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "Command.h"
#include <string.h>

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
      // Check for exit command
      // FIXME: We want to have a proper exit status passed back up to main()
      // Fix this so that we don't need to do an ugly string comparison to hard exit
      // out of the process.
      // Within Line::execute()
      // for i = 1 to tree_record.size()
      // if ( !tree_record.at(i)->execute) return false;
      std::string exitString("exit");
      if ( this->exec_name == exitString )
      {
          exit(1);  
      }
      
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
     
      char** updated_array = new char*[array_size + 2];
      //setting all the null first, because null checks for control later on
      for (int i = 0; i < (array_size + 2); i++)
        updated_array[i] = NULL;

      updated_array[0] = this->exec_name;

      //copy original array
      for (unsigned i = 1; this->args[i - 1] != NULL; i++) 
        updated_array[i] = this->args[i - 1];
 
      delete [](this->args);
      return updated_array;
    }
    
    void print() {
      this->args = prepend_char_pointer_array();
      std::cout << "process " << this->exec_name << " with args: \n";
      for (unsigned i = 0; this->args[i] != NULL; i++)
        std::cout << this->args[i] << " ";
      std::cout << std::endl << std::endl;
    }
};
	
#endif
