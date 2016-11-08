#include "Parser.h"
#include <iostream>
#include "Line.h"
#include "Command.h"

int main() {
  std::string input = "";
  std::cout << input << std::endl;
  Parser foo(input);
  Line* line = foo.parse();
  return 0;
}


