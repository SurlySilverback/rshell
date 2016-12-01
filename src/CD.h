#ifndef CD_H
#define CD_H
#include "Command.h"
#include <unistd.h>
#include <stdlib.h>
#include <libgen.h>

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
    setenv("PWD", getenv(HOME_ENV_KEY), 1);
    chdir(getenv("program_root"));
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
    
    char* new_dir = dirname( getenv("PWD") );   

    setenv("OLDPWD", getenv("PWD"), 1);
    setenv("PWD", new_dir, 1);
    chdir(new_dir);
    
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
char* CD::extract_first_dir_name(char* to_extract) const {
 
  char* extracted_dir_name = new char[get_array_length(to_extract)];
  
  unsigned int i;
  //extract from different indices based on if first element is '/'
  if (to_extract[0] == '/') {
    for (i = 1; to_extract[i] != '\0'; i++) { 
      if (to_extract[i] == '/')
        break;
      extracted_dir_name[i - 1] = to_extract[i];
    }
    extracted_dir_name[i - 1] = '\0';
  }

  else {  
    for (i = 0; to_extract[i] != '\0'; i++) {
      if (to_extract[i] == '/')
        break;
      extracted_dir_name[i] = to_extract[i];
    }
    extracted_dir_name[i] = '\0';
  }
 
  return extracted_dir_name;     
} 

#endif
