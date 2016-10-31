#ifndef PROCESS_H
#define PROCESS_H

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

class Process: public Command {

  public:
	Process(){};
	
	void execute(){
	
      pid_t pid;
		
	  pid = fork();
		
	  if ( pid == 0 ){
        //child
		// child calls execpvp() with char[] passed from parser
	  }
	  
	  if ( pid > 0 ){
	    //parent    
		// Parent should monitor child's running status
	  }
		
	
  private:
    
    
};
	
#endif