#ifndef OR_H
#define OR_H

#include "Command.h"

class Or: public Command {
  public:
    Or(Command *lhs = NULL, Command *rhs = NULL) {
      this->LHS = lhs;
      this->RHS = rhs;
    }

    //NOTE: currently, 'true' is returned if there exists one child which properly executes.	
    //      Should this unconditionally return 'false' if there is only one child?
    //      in the actual shell, execution hangs if a connector is missing a child
    bool execute() {
      
      if (this->LHS != NULL) { 
        if (this->LHS->execute())
          return true; 
      }

      if (this->RHS != NULL)
        return this->RHS->execute();

      return false;
    }
    
    void print() {
    }

  private:
    Command *LHS, *RHS;
};

#endif
