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
  char* append_relative_path() const;
  unsigned int get_array_length(char*) const; 
  void append_to_array(char*, char*, int) const;
};

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

  // If the entry is "cd .."
  if ( static_cast<std::string>(this->path) == ".." ){
    char* temp = getenv("PWD");
    int pwd_count = 0;
    for (unsigned i = 0; temp[i] != '\0'; ++i)
      ++pwd_count;

    
  }

  // If the entry is "cd <PATH>"
  if (chdir(this->path) == 0) {
    setenv("OLDPWD", getenv("PWD"), 1);
    setenv("PWD", append_relative_path(), 1);
    return true; 
  }

  return false;
}

char* CD::append_relative_path() const {
  char* current_dir = getenv("PWD");
  unsigned int curr_char_count     = get_array_length(current_dir);
  unsigned int rel_path_char_count = get_array_length(this->path);
                 
  //allocate for updated path (+ 2 for these chars)
  char* updated_directory = new char[curr_char_count + rel_path_char_count + 2];
    
  //copy current path
  append_to_array(updated_directory, current_dir, 0);

  unsigned i = 0;
  for (i = 0; this->path[i] != '\0'; i++)
    updated_directory[curr_char_count + i] = this->path[i];  
    updated_directory[curr_char_count + i] = '\0';

  //append forward slash
  std::string path_delim = "/";
  char* path_delim_char = new char;
  strcpy (path_delim_char, path_delim.c_str());  
  append_to_array(updated_directory, path_delim_char, curr_char_count);
  delete path_delim_char;
  
  //append relative path
  append_to_array(updated_directory, this->path, curr_char_count + 1);

  return updated_directory;
}


unsigned int CD::get_array_length(char* to_count) const {
  unsigned int count = 0;

  for (unsigned i = 0; to_count[i] != '\0'; i++)
    count++; 
  return count;
}

void CD::append_to_array(char* to_append, char* appending_chars, int copy_offset) const {
  for (int i = 0; appending_chars[i] != '\0'; i++)
    to_append[copy_offset + i] = appending_chars[i];
}

#endif
