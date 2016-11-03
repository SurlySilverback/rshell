#ifndef LINE_H
#define LINE_H

#include "Command.h"
#include <vector>

class Line: public Command{

  public:
    Line(){};
	
/***********************************************************
 Line->execute(): Because line contains a vector of base
     pointers to potentially multiple commends, it calls the
     execute() functions of all of its owned Processes in a
     loop.
***********************************************************/  
	  void execute(){
    
      for (unsigned int i = 0; i < memory.sizeof(); ++i){
        
        memory.at(i)->execute();
        std::cout << std::endl;
      }
    }
  
  private:
  	vector<Command*> memory;
	
};

#endif