#include <iostream>
#include "Command.h"
#include "And.h"
#include "Or.h"
#include "Process.h"
#include "Line.h"
#include <string>

int main(){

  // instantiate a Parser object here
  int status = 0;
  std::string user_input;
  
  do {
    
    getline( cin, user_input );
    Line* l = new Parser(user_input);
    l->execute();
    
  } while ( status != 0 );
  

  return 0;
}
