#ifndef CD_H
#define CD_H
#include "Command.h"
#include <unistd.h>
#include <stdlib.h>

#define HOME_ENV_KEY "program_root"

class CD: public Command {
  char* path;
 
  public:
    CD(char* path) { this->path = path; }
    bool execute();

  private:
    char*        append_relative_path() const;
    unsigned int get_array_length(char*) const; 
    void         append_to_array(char*, char*, int) const;
    char*        string_to_char_ptr(std::string to_convert) const;
    bool         is_explicit_path() const;
    char*        extract_first_dir_name(char*) const;
};

bool CD::execute() {
  //if no specified path, default to home
  if ( this->path == NULL ) { 
    chdir(getenv("program_root"));
    setenv("PWD", getenv(HOME_ENV_KEY), 1);
    return true;
  }

  //step back
  if (this-> path[0] == '-'){
    //This will be a classic two-variable swap using a temp as an intermediary placeholder
    char* temp = getenv("PWD");
    setenv("PWD", getenv("OLDPWD"), 1);
    setenv("OLDPWD", temp, 1);
    chdir( getenv("PWD") );
    return true;
  } 

  // If the entry is "cd .."
  if ( static_cast<std::string>(this->path) == ".." ){
    // Check here to make sure we're not at ~

    // First, get the current path
    char* temp = getenv("PWD");
    int pwd_count = 0;
    int fwd_slash_pos = 0;

    // Find the length of the current path
    for (unsigned i = 0; temp[i] != '\0'; ++i){
      ++pwd_count;
    }
    // Starting from the end of the current path, count backwards until the first fwd slash is found
    for (unsigned i = pwd_count; temp[i] != '/'; --i){
      ++fwd_slash_pos;
    }
    // Make a new char* of length original minus fwd slash position
    char* up_dir = new char[(pwd_count - fwd_slash_pos)];

    // Copy over the string, minus everything after the fwd slash
    unsigned int i = 0;
    for (i = 0; i < pwd_count - fwd_slash_pos; ++i){
      up_dir[i] = temp[i];
    }
    // Append a null terminator
    up_dir[i] = '\0';

    setenv("OLDPWD", getenv("PWD"), 1);
    setenv("PWD", getenv(up_dir), 1);
    chdir(up_dir);
    
    return true;
  }

  //If the entry is "cd <PATH>"
  if (chdir(this->path) == 0) {
    setenv("OLDPWD", getenv("PWD"), 1);

    if (is_explicit_path())
      setenv("PWD", this->path, 1);
    else
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
    
  //append current directory
  append_to_array(updated_directory, current_dir, 0);
  
  //append forward slash
  char* path_delim = string_to_char_ptr("/");
  append_to_array(updated_directory, path_delim, curr_char_count);
  delete path_delim;  

  //append relative path
  append_to_array(updated_directory, this->path, curr_char_count + 1);

  //append null char
  char* terminating_char = string_to_char_ptr("\0");
  append_to_array(updated_directory, terminating_char, curr_char_count);
  delete terminating_char;
  
  return updated_directory;
}

unsigned int CD::get_array_length(char* to_count) const {
  unsigned int count = 0;

  for (unsigned i = 0; to_count[i] != '\0'; i++)
    count++; 
  return count;
}

char* CD::string_to_char_ptr(std::string to_convert) const {
  char* converted = new char;
  strcpy (converted, to_convert.c_str());

  return converted;
}

void CD::append_to_array(char* to_append, char* appending_chars, int copy_offset) const {
  for (int i = 0; appending_chars[i] != '\0'; i++)
    to_append[copy_offset + i] = appending_chars[i];
}

//determines whether argument is an explicit path based on whether the argument follows the pattern '/<home_directory_name>'
bool CD::is_explicit_path() const{
  char* home_directory = getenv(HOME_ENV_KEY);

  if (this->path == NULL)
    return false;  

  else if (static_cast<std::string>(this->path) == "/")
    return true;

  else if (this->path[0] == '/') {
    char* first_directory_root = extract_first_dir_name(home_directory); 
    char* first_directory_path = extract_first_dir_name(this->path);

    if (*first_directory_root == *first_directory_path) {
      delete first_directory_root;
      delete first_directory_path;
      
      return true;
    } 
    delete first_directory_root;
    delete first_directory_path;
  }
    
  return false; 
}

//this method parses the 'home' path and extracts the name of the first highest-level directory immediately under root
char* CD::extract_first_directory(char* to_extract) const {
  char* extracted_dir_name = new char[get_array_length(to_extract)];

  //extract from different indices based on if first element is '/'
  if (to_extract[0] == '/') {
    for (unsigned i = 1; to_extract[i] != '\0'; i++) { 
      if (to_extract[i] == '/')
        break;
      extracted_dir_name[i - 1] = to_extract[i];
    }
    extracted_dir_name[i - 1] = '\0';
  }

  else {  
    for (unsigned i = 0; to_extract[i] != '\0'; i++) {
      if (to_extract[i] == '/')
        break;
      extracted_dir_name[i] = to_extract[i];
    }
    extracted_dir_name[i] = '\0';
  }
 
  return extracted_dir_name;     
} 

#endif
