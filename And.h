#ifndef AND_H
#define AND_H

#include "Command.h"

class And: public Command{

  public:
    And(Command *lhs, Command *rhs){ 
      this->LHS = lhs;
      this->RHS = rhs;
    }
    
    void execute(){
      if (this->is_valid()) {    
        if ( my_parent == NULL ) {
          if (this->LHS != NULL)        
            LHS->execute();
          if (this->RHS != NULL)
            RHS->execute();
        } 
      }
    }
  
    bool is_valid(){   
      if (this->LHS != NULL) {
        if (this->LHS->is_valid()) {
          if (this->RHS != NULL) {
            if (this->RHS->is_valid())
              return true;
          }
        }
      }
      return false;
    }
	
  private:
    Command *my_parent, *LHS, *RHS;
};

#endif
