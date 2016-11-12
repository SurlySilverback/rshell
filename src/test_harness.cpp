#include "Parser.h"
#include <iostream>
#include "Line.h"
#include "Command.h"

int main() {
  do 
  {
       std::cout << "$ ";

       std::string input;

       getline(input, cin);
  
       Parser foo(input);
  
       Line* line = foo.parse();

       std::cout << endl;

  } while ( status != 0 )

 return 0;
}

