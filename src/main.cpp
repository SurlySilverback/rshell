#include <iostream>
#include "Command.h"
#include "And.h"
#include "Or.h"
#include "Process.h"
#include "Line.h"
#include "Parser.h"
#include <string>

int main(){

  // instantiate a Parser object here
  int status = 0;
  std::string user_input;
  
  do {
    std::cout << "$";
    getline( std::cin, user_input );
    Parser* p = new Parser(user_input);
    Line* l = p->parse();
    l->execute();
    
  } while ( status != 0 );
  

  return 0;
}
