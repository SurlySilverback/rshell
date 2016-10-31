#ifndef OR_H
#define OR_H

#include "Command.h"

class Or: public Command{

  public:
    Or(Command *lhs, Command *rhs){
    
      this->LHS = lhs;
      this->RHS = rhs;
    }
	
    void execute(){
      
      if ( this->is_valid() ){
        
        if ( my_parent == NULL ){
          
          if ( left_success == true )
            LHS->execute();
      
          else if ( right_success = true )
            RHS->execute();
        }
      }
    }
  
    bool is_valid(){
    
      if ( LHS->is_valid() ){
        
        left_success = true;
        return true;
      }
      
      else if ( RHS->is_valid() ){
      
        right_success = true;
        return true;
      }
        
      else
        return false;
    }
  
	  // bool success(); // FIXME Is this function still necessary?
	
  private:
	  Command *my_parent = NULL, *LHS = NULL, *RHS = NULL;
	  bool left_success = 0, right_success = 0;
};

#endif