#ifndef DUMMY_H
#define DUMMY_H

#include "Command.h"

class Dummy: public Command{

  public:
    Dummy(){};
	
	void execute(){};
  
    bool is_valid(){
    
      return false;
    }
	
	  /* FIXME Some indeterminate helper functions should go here */
	
  private:
	  Command *my_parent = NULL;
};

#endif