#ifndef PROCESS_H
#define PROCESS_H

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

class Process: public Command {

  public:
    Process(){};
	
    void execute(){		

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
		
	
  private:
    
    
};
	
#endif
