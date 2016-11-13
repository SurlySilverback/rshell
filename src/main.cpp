#include <string.h>
#include <iostream>
#include "Parser.h"
#include "Line.h"
#include "Command.h"

int main() {
  
  int status = 0;
  
  do 
  {
       std::cout << "$ ";

       std::string input;
    
       getline(std::cin, input);
  
       Parser foo(input);
  
       Line* line = foo.parse();
    
       status = line->execute();

       std::cout << std::endl;

  } while ( status != 0 );

 return 0;
}

