//*****************
//TOKEN_INTERPRETER
//*****************
// -methods used throughout each parse cycle to get information about token
// -one interpreter per token

#ifndef TOKEN_INTERPRETER_H
#define TOKEN_INTERPRETER_H
#include <stdexcept>
#include <cstdlib>
#include "Tree_Construct_Record.h"

enum TOKEN_TYPE {COMMENT, CONNECTOR, ARGUMENT, COMMAND, PRECEDE_CHAR, TEST, DIR_CHANGE};

//NOTES:
//  -definition guard because also defined in Tree_Construct_Record.h
//  -strings in CONNECTORS array must correspond with their respective enumerated int values
#ifndef CONNECTOR_TYPES
#define CONNECTOR_TYPES
#define CONNECTOR_NUM 3
static const std::string CONNECTORS[CONNECTOR_NUM] = {"&&", "||", ";"};
enum CONNECT_TYPE {AND, OR, END};
#endif

class Token_Interpreter {
  private: 
    char*        token;
    bool         closure_char;
    char         preced_char;
  public:
                 Token_Interpreter(char*);
    TOKEN_TYPE   token_type(Tree_Construct_Record*);
    CONNECT_TYPE connect_type() const;
    char         preced_char_type() const;
    bool         contains_closure_char() const;

  private:
    bool         is_comment() const;
    bool         is_connector() const;
    void         filter_closure_char();
    bool         is_precede_char();
    bool         is_test(Tree_Construct_Record*) const;
    bool         is_cd() const;
};

Token_Interpreter::Token_Interpreter(char* token) {
  this->token = token;
  this->preced_char = '\0';
  
  //the reasoning for closure_char initially being set false is explained
  //in the method's definition
  this->closure_char = false;
  if (contains_closure_char()) {
    closure_char = true;
    filter_closure_char();
  }
}

TOKEN_TYPE Token_Interpreter::token_type(Tree_Construct_Record* record) {
  Tree_Construct_Record* youngest_child_record = record;
  while (youngest_child_record->pend_preced_op)
    youngest_child_record = youngest_child_record->child_record;

  if (is_comment()) 
    return COMMENT;
  else if (is_connector())
    return CONNECTOR;
  else if (is_precede_char())
    return PRECEDE_CHAR;

  //comments, connectors, and precedence chars terminate the process of accumulating process/test construction data,
  //therefore, if there is an object pending construction, all tokens which are non accumulation-terminating are arguments
  else if (youngest_child_record->pend_process_init || youngest_child_record->pend_test_init || youngest_child_record->pend_dir_change)
    return ARGUMENT;

  else if (is_test(record))
    return TEST;
  else if (is_cd()) 
    return DIR_CHANGE;
  else
    return COMMAND;
}

//notes: 
//  1.) closure_char is initially set to false in constructor; this design allows
//      for the filtering of the closure_char while still having record that it 
//      was originally in the token
//  2.) this method only checks if closure char was last element of token
bool Token_Interpreter::contains_closure_char() const {
  if (!this->closure_char) {
    unsigned i;
    //get index of last char
    for (i = 0; this->token[i] != '\0'; i++) {}
    i--;

    if (this->token[i] == ';')
      return true;
    return false;
  }
  else
    return true;
}

CONNECT_TYPE Token_Interpreter::connect_type() const {
  for (unsigned i = 0; i < CONNECTOR_NUM; i++) {
    if (token == CONNECTORS[i]) {
      //connector's indices correspond with their enum values
      return static_cast<CONNECT_TYPE>(i); 
    }
  }
  //FIXME: replace with thrown exception
  exit(1); 
}

char Token_Interpreter::preced_char_type() const {
  return this->preced_char;
}

bool Token_Interpreter::is_comment() const {
  for (unsigned i = 0; this->token[i] != '\0'; i++) {
    if (this->token[i] == '#')
      return true;
  }
  return false;
}

bool Token_Interpreter::is_connector() const {
  for (unsigned i = 0; i < CONNECTOR_NUM; i++) {
    if (this->token == CONNECTORS[i])
      return true;
  }
  return false;
}

//get index of last char (the closure that will be filtered) and replace with null char
void Token_Interpreter::filter_closure_char() {
  unsigned i;
  for (i = 0; this->token[i] != '\0'; i++) {}
  i--;

  this->token[i] = '\0';
}

//FIXME: will need to strip rest of string from char
bool Token_Interpreter::is_precede_char() {
  //get index of last char
  unsigned i = 0;
  while(this->token[i] != '\0')
    i++;
  i--;

  if (static_cast<std::string>(this->token) == "(" || this->token[0] == '(') {    
    this->preced_char = '(';
    return true;
  }
  if (static_cast<std::string>(this->token) == "]" || this->token[i] == ')') { 
    this->preced_char = ')';    
    return true; 
  }
  return false;
}

bool Token_Interpreter::is_test(Tree_Construct_Record* record) const {
  //get index of last char
  unsigned i = 0;
  while(this->token[i] != '\0')
    i++;
  i--;

  if (static_cast<std::string>(this->token) == "test" || 
      static_cast<std::string>(this->token) == "[" || 
      this->token[0] == '[' || 
      static_cast<std::string>(this->token) == "]" ||
      this->token[i] == ']') 
  {
    Tree_Construct_Record* youngest_child_record = record;
    while (youngest_child_record->pend_preced_op)
      youngest_child_record = youngest_child_record->child_record;
    
    //this allows 'test, '[', and ']' to be passed as arguments to other processes
    if (!youngest_child_record->pend_process_init)  
      return true; 
  }  

  return false;
}

bool Token_Interpreter::is_cd() const {
  if (static_cast<std::string>(this->token) == "cd")
    return true;
  return false;
}
#endif
