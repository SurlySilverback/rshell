#include "Parser.h"
#include <iostream>
#include "Line.h"
#include "Command.h"

int main() {
  
  int status = 0;
  
  do 
  {
       //std::cout << "$ ";

       std::string input = "echo foo && echo bar && ls";

       //getline(input, std::cin);
  
       Parser foo(input);
  
       Line* line = foo.parse();
    
       status = line->execute();

       std::cout << std::endl;

  } while ( status != 1 );

 return 0;
}

