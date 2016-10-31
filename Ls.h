#ifndef LS_H
#define LS_H

#include "Command.h"

class Ls: public Command{

  public:
    Ls(){};
	
	  void execute(){
    
      std::cout << "Listing directories...done!"; // FIXME Test cout
    }
  
    bool is_valid(){
    
      return true;
    }
	
	  /* FIXME Some indeterminate helper functions should go here */

  private:
	  Command *my_parent;
	
};

#endif