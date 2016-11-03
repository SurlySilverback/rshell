#include "Parser.h"
#include <iostream>

int main() {
  Parser foo("echo foo || mkdir bar");
  foo.parse();
  return 0;
}


