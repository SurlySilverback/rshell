#include <iostream>
#include "Command.h"
#include "And.h"
#include "Or.h"
#include "Process.h"
#include "Line.h"
#include "Parser.h"
#include <string>
#include <vector>

int main(){

  // instantiate a Parser object here
  int status = 0;
  std::string user_input;
  
  do {
    // FIXME: Uncomment this stuff to get the program working normally again
    //std::cout << "$";
    //getline( std::cin, user_input );
    //Parser* p = new Parser(user_input);
    //Line* l = p->parse();
    
    
    //FIXME: Test block - building a tree manually
    
    //First, make the strings
    char *echo;
    std::string Echo = "echo";
    strcpy( echo, Echo.c_str() );
    
    char *hello;
    std::string Hello = "Hello";
    strcpy( hello, Hello.c_str() );
    
    char *world;
    std::string World = "World";
    strcpy( world, World.c_str() );
    
    char *ls;
    std::string Ls = "ls";
    strcpy( ls, Ls.c_str() );
    
    //Next, make the arg strings with the executable name in the first index
    char **exargs1 = new char*[2];
    exargs1[0] = echo;
    exargs1[1] = hello;
    
    char **exargs2 = new char*[2];
    exargs2[0] = echo;
    exargs2[1] = world;
    
    char **exargs3 = new char*[2];
    exargs3[0] = ls;
    exargs3[1] = ls;
    
    //Instantiate the Process objects with the above as arguments
    Process *echoHello = new Process(echo, exargs1);
    Process *echoWorld = new Process(echo, exargs2);
    Process *lsCom = new Process(ls, exargs3);
    
    //Pass the Process objects into the manually-built Command tree
    Command *andCom1 = new And(echoHello, echoWorld);
    Command *andCom2 = new And(andCom1, lsCom);
      
    std::vector<Command*> test_array;
    test_array.push_back(andCom2);
    
    test_array[0]->execute();
    
  } while ( status != 0 );
  

  return 0;
}
