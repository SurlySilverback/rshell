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
    char* exec_name;  // name of executable
    char** args;      // 2d char array containing flags, aruments, etc
                      // args must be rebuilt to include exec_name in first index
  public:
    Process(char* exec_name, char** args) { 
      // exec_name is the name of the executable
      this-> exec_name = exec_name; 
      
      int counter = 1;
      
      for (unsigned i = 0; args[i]!= NULL; ++i)
        counter++;
      
      this-> args = new char*[counter];
      this-> args[0] = exec_name;
      
      for (unsigned i = 1; i < counter; ++i){
        
        this-> args[i] = args[i];
      }
    };

    bool is_valid() {
      return true;
    }

    void execute() {
      		
      pid_t pid = fork();		
      
      if ( pid == -1 ){
        perror("fork");
      }

      if ( pid == 0  ){
        //child     
        if ( execvp( exec_name, args ) == -1 )
          perror("exec");

      }
     
      if ( pid > 0 ){
        //parent
        wait(0);    
        // FIXME Parent should monitor child's running status
      }
      
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
