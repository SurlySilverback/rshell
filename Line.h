#ifndef LINE_H
#define LINE_H

#include "Command.h"
#include <vector>

class Line: public Command{

  public:
    Line(){};
	
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