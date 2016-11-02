#include <iostream>
#include "Command.h"
#include "And.h"
#include "Or.h"
#include "Echo.h"
#include "Ls.h"
#include "Mkdir.h"
#include "Dummy.h"

int main(){

  // instantiate a Parser object here
  int status = 0;
  
  
  do {
    
    // take in line from user
    // Process obect = Parser(userline);
    // Process->execute();
    
  } while ( status != 0);
  
  
  /************************************** 
   Testing: output is: "Hello"
  
         OR
         /\
       OR  echo2
       /\
  echo1  ls
  
  **************************************/
  /*
  Echo *echo1 = new Echo("Hello");
  Echo *echo2 = new Echo("World");
  Ls *ls1 = new Ls;
  Or *or1 = new Or(echo1, ls1);
  Or *or2 = new Or(or1, echo2);

  or2->execute();


  /************************************** 
   Testing
  
         AND
         /\
       OR  echo1
       /\
 dummy1  ls1
  
  **************************************/
  /*
  Echo *echo1 = new Echo("Hello");
  Dummy *dummy1 = new Dummy;
  Ls *ls1 = new Ls;
  Or *or1 = new Or(dummy1, ls1);
  And *and1 = new And(or1, echo1);

  and1->execute();
  
  
  /************************************** 
   Testing
  
         AND
         /\
       OR  echo1
       /\
 dummy1  dummy2
  
  **************************************/
  /*
  Echo *echo1 = new Echo("Hello");
  Dummy *dummy1 = new Dummy;
  Dummy *dummy2 = new Dummy;
  Or *or1 = new Or(dummy1, dummy2);
  And *and1 = new And(or1, echo1);

  and1->execute();
  
*/
  
  do {

    // Take input from user
    // Feed input to parser
    // parserobject->execute();


  } while(/*status!=exit integer*/)

  return 0;
}
