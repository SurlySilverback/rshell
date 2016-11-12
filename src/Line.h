#ifndef LINE_H
#define LINE_H

#include "Command.h"
#include <vector>

class Line: public Command{
  public:
    Line(std::vector<Command*> tree_array) {
      this->process_trees = tree_array;
      
      // FIXME: Test cout
      //std::cout << "Line Constructor: done building Line " << std::endl;
    }

    bool execute()
    { 
      for (unsigned int i = 0; i < process_trees.size(); ++i)
          process_trees.at(i)->execute();
      
      return true;
    }
    
  private:
    std::vector<Command*> process_trees;	
};
#endif
