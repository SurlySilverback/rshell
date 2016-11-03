#ifndef PROCESS_H
#define PROCESS_H

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include "Command.h"

class Process: public Command {
  private:
    char* exec_name;
    char** args;

  public:
    Process(char* exec_name, char** args) { 
      this-> exec_name = exec_name; 
      this-> args = args;
    };

    bool is_valid() {
      return true;
    }

    void execute() {
      /*		
      pid_t pid = fork();		
      
      if ( pid == -1 ){
        perror("fork");
      }

      if ( pid == 0  ){
        //child     
        if ( execvp() == -1 )
          perror("exec");
        // child calls evecvp() here with char* and char*[]
      }
     
      if ( pid > 0 ){
        //parent
        wait(0);    
        // FIXME Parent should monitor child's running status
      }
      */
    }

   //FIXME: DEBUG print
   void print() {
     std::cout << "process name\n";
     std::cout << this->exec_name << "\n";
    
     for(unsigned i = 0; this->args[i] != NULL; i++) { 
       std::cout << args[i] << " "; 
     }
     std::cout << std::endl;
   }
};
	
#endif
