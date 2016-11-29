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

  bool execute();
private:
  char* append_relative_path(); 
};

//FIXME: distinguish between relative and explicit paths
//NOTE: since a relative path cannot be prepended with '/', setenv will omit them
//      in the updated path in the prompt
bool CD::execute() {
  
  // If the entry is "cd"
  if ( this->path == NULL ) { 
    chdir(getenv("program_root"));
    setenv("PWD", getenv("program_root"), 1);
    return true;
  }

  // If the entry is "cd -"
  if ( this-> path[0] == '-'){
    // This will be a classic two-variable swap using a temp as an intermediary placeholder
    char* temp = getenv("PWD");
    setenv("PWD", getenv("OLDPWD"), 1);
    setenv("OLDPWD", temp, 1);
    chdir( getenv("PWD") );
    return true;
  } 

  // If the entry is "cd <PATH>"
  if (chdir(this->path) == 0) {
    setenv("OLDPWD", "PWD", 1);
    setenv("PWD", append_relative_path(), 1);
    return true; 
  }

  return false;
}

char* CD::append_relative_path() {
  char* current_dir = getenv("PWD");
  unsigned int old_char_count = 0;

  //get length of directory path that is being appended
  for (unsigned i = 0; current_dir[i] != '\0'; i++)
    old_char_count++; 
           
  //get length of relative path that will be appended
  unsigned int relative_char_count = 0;
  for (unsigned i = 0; this->path[i] != '\0'; i++)
    relative_char_count++; 
      
  //append path to old
  char* updated_directory = new char[old_char_count + relative_char_count + 1];
    
  for (unsigned i = 0; current_dir[i] != '\0'; i++)
    updated_directory[i] = current_dir[i];      

  unsigned i = 0;
  for (i = 0; this->path[i] != '\0'; i++)
    updated_directory[old_char_count + i] = this->path[i];  
    updated_directory[old_char_count + i] = '\0';

  return updated_directory;
}

#endif
