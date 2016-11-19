#ifndef LINE_H
#define LINE_H

#include "Command.h"
#include <vector>

class Line: public Command{
  public:
    Line(std::vector<Command*> tree_array) {
      this->process_trees = tree_array;
    }

    bool execute()
    { 
        for (unsigned int i = 0; i < process_trees.size(); ++i)
        {    
            if ( !process_trees.at(i)->execute() )
            {
                return false;
            }
        }
        return true;
    }

  void print() {
    for (unsigned i = 0; i < process_trees.size(); i++) 
      process_trees.at(i)->print();
  }
    
  private:
      std::vector<Command*> process_trees;	
};
#endif
