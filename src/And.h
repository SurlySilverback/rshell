#ifndef AND_H
#define AND_H

#include "Command.h"

class And: public Command{

  public:
    And(Command *lhs, Command *rhs){ 
      this->LHS = lhs;
      this->RHS = rhs;
    }
    
    //only returns true if there are two children, and both execute properly
    bool execute(){
      if (this->LHS != NULL) {      
        if (this->LHS->execute()) {
          if (this->RHS != NULL)
            return this->RHS->execute(); 
        }
      }
      return false;
   }

  void print() {
    std::cout << "connector AND with children:\n";
    if (this->LHS != NULL) 
      this->LHS->print();
    if (this->RHS != NULL)
      this->RHS->print();
  }
  	
  private:
    Command *LHS, *RHS;
};

#endif
