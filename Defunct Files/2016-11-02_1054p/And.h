#ifndef AND_H
#define AND_H

#include "Command.h"

class And: public Command{

  public:
    And(Command *lhs, Command *rhs){
    
      this->LHS = lhs;
      this->RHS = rhs;
    }
  
	  And(){};
	
/************************************************************************
 And->execute(): Checks to ensure that its left-hand and right-hand
     children both return true using is_valid() before calling execute.
************************************************************************/
	  void execute(){
    
      if ( this->is_valid() ){
        
        // If I am the top of the tree, I will begin the recursive execute call
        if ( my_parent == NULL ){
          
          LHS->execute();
          RHS->execute();
        } 
      }
    }
  
  
/************************************************************************
 And->is_valid(): Checks to ensure that its left-hand and right-hand
     children both return true.
************************************************************************/
    bool is_valid(){
    
      if ( LHS->is_valid() && RHS->is_valid() )
        return true;
      
      else
        return false;
    }
	
  private:
	  Command *my_parent = NULL, *LHS = NULL, *RHS = NULL;
};

#endif