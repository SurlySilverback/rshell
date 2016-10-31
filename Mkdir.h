#ifndef MKDIR_H
#define MKDIR_H

#include "Command.h"

class Mkdir: public Command{

  public:
    Mkdir(){};
	
	  void execute(){
    
      std::cout << "Creating directory...done!";
    }
	  
    bool is_valid(){
    
      return true;
    }
	  /* FIXME Some indeterminate helper functions should go here */
	
  private:
	  Command *my_parent;
	
};

#endif