#ifndef OR_H
#define OR_H

#include "Command.h"

class Or: public Command{
  public:
    Or(Command *lhs, Command *rhs){
      this->LHS = lhs;
      this->RHS = rhs;
      this->left_success = false;
    }
	
    void execute() {
      if (this->is_valid()) {
        if (my_parent == NULL) {
          if (left_success)
            LHS->execute(); 
          else
            RHS->execute();
        }
      }
    }
  
    bool is_valid(){
      if (this->LHS != NULL) {  
        if (LHS->is_valid()) {
          this->left_success = true;
          return true;
        }
      }
   
      else if (this->RHS != NULL) {
        if (this->RHS->is_valid()
          return true;
      }

      return false;  
    }
	
  private:
    Command *my_parent, *LHS, *RHS;
    bool left_success;
};

#endif
