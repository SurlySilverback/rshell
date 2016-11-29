#ifndef CD_H
#define CD_H
#include "Command.h"
#include <unistd.h>
#include <stdlib.h>

class CD: public Command {
  char* path;
 
 public:
    CD(char* path) {
      this->path = path;
    }

    bool execute() {


      //appends this->path to the PWD directory
      //note that '/' needs to prepended when inputting cd arguments while running in the shell
      
      chdir(this->path);
      /*
      char* current_dir = getenv("PWD");
      unsigned int old_char_count = 0;

      for (unsigned i = 0; current_dir[i] != '\0'; i++)
        old_char_count++; 
           
      unsigned int relative_char_count = 0;
      for (unsigned i = 0; this->path[i] != '\0'; i++)
        relative_char_count++; 
      
      char* updated_directory = new char[old_char_count + relative_char_count + 1];
    
      for (unsigned i = 0; current_dir[i] != '\0'; i++)
         updated_directory[i] = current_dir[i];      

      unsigned i = 0;
      for (i = 0; this->path[i] != '\0'; i++)
         updated_directory[old_char_count + i] = this->path[i];  

      updated_directory[old_char_count + i] = '\0';
      */
    
      std::cout << "OLDPWD is: " << getenv("OLDPWD") << std::endl;
      std::cout << "PWD is:    " << getenv("PWD") << std::endl;

      setenv( getenv("PWD"), getenv("OLDPWD"), 1);
      setenv( this->path, getenv("PWD"), 1);
      
      return true;
    }
};
#endif
