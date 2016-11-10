#ifndef AND_H
#define AND_H

#include "Command.h"

class And: public Command{

  public:
    And(Command *lhs, Command *rhs){
    
      this->LHS = lhs;
      this->RHS = rhs;
    }  // FIXME Only for test values
  
	  And(){};
	
	  void execute(){
    
      if ( this->is_valid() ){
      
        if ( my_parent == NULL ){
          
          LHS->execute();
          RHS->execute();
        } 
      }
    }
  
    bool is_valid(){
    
      if ( LHS->is_valid() && RHS->is_valid() )
        return true;
      
      else
        return false;
    }
  
   //FIXME: DEBUG print
   /*void print() {
     std::cout << "connector: AND \nchildren: ";
     this->LHS->print();
     this->RHS->print(); 
     std::cout << std::endl;   
   }*/


	  // bool success(); // FIXME Is this function still needed?
	
  private:
	  Command *my_parent, *LHS, *RHS;
};

#endif
