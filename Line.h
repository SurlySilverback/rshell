#ifndef LINE_H
#define LINE_H

#include "Command.h"
#include <vector>

class Line: public Command{

  public:
    Line(std::vector<Command*> tree_array) {
      this->memory = tree_array;
    }
    void execute(){ 
      for (unsigned int i = 0; i < memory.size(); ++i) {
        memory.at(i)->execute();
      }
    }
    bool is_valid() { return true; }
    void print() {}
    
  private:
    std::vector<Command*> memory;	
};
#endif
