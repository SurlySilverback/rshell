#ifndef OR_H
#define OR_H

#include "Command.h"

class Or: public Command{

  public:
    Or(Command *lhs, Command *rhs){
      this->LHS = lhs;
      this->RHS = rhs;
    }

/************************************************************************
 Or->execute(): Checks to ensure that either its left-hand or right-hand
     child returns true using is_valid() before calling execute on the
     child that returned successful.
************************************************************************/
    void execute(){
      
      if ( this->is_valid() ){
        
        if ( my_parent == NULL ){
          
          if ( left_success == true )
            LHS->execute();
      
          else if ( right_success == true )
            RHS->execute();
        }
      }
    }
  
/************************************************************************
 Or->is_valid(): Checks to ensure that either its left-hand or right-hand
     child returns true.
************************************************************************/
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
  
   //FIXME: DEBUG print
   void print() {
     std::cout << "OR - children:\n";
     if (this->LHS != NULL)
       this->LHS->print();
     if (this->RHS != NULL)
       this->RHS->print();

     std::cout << std::endl;   
   }


	  // bool success(); // FIXME Is this function still necessary?
	
  private:
	  Command *my_parent, *LHS, *RHS;
	  bool left_success, right_success;
};

#endif
