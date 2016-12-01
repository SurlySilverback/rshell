#include <string.h>
#include <iostream>
#include "Parser.h"
#include "Line.h"
#include "Command.h"
#include <unistd.h>
#include <stdlib.h>

#ifndef HOME_ENV_KEY
#define HOME_ENV_KEY "program_root"
#endif

int main() { 
  int status = 0;
  setenv(HOME_ENV_KEY, getenv("PWD"), 1); 

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

