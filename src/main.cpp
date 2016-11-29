#include <string.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include "Parser.h"
#include "Line.h"
#include "Command.h"
#include <unistd.h>
#include <stdlib.h>

int main() { 
  int status = 0;

  setenv("program_root", getenv("PWD"), 1); 
  std::cout << "setting program_root to " << getenv("program_root") << std::endl << std::endl; 

  do 
  {
       std::cout << getenv("PWD") << "$ ";

       std::string input;
    
       getline(std::cin, input);
  
       Parser foo(input);
  
       Line* line = foo.parse();
    
       status = line->execute();

       std::cout << std::endl;

  } while ( status != 0 );

 return 0;
}

