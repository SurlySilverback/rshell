#ifndef ECHO_H
#define ECHO_H

#include "Command.h"
#include <string>

class Echo: public Command{

  public:
    Echo(std::string arg){
    
      echo_out = arg;
    }
	
	  void execute(){
      
      std::cout << echo_out;
    }
  
    bool is_valid(){
    
      return true;
    }
	
	  /* FIXME Some indeterminate helper functions should go here */
	
  private:
	  Command *my_parent;
    std::string echo_out;
	
};

#endif