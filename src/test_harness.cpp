#include "Parser.h"
#include <iostream>
#include "Line.h"
#include "Command.h"

int main() {
  std::string input = "echo foo && echo bar";
  std::cout << input << std::endl;
  Parser foo(input);
  Line* line = foo.parse();
  return 0;
}

