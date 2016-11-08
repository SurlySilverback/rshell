#ifndef TOKEN_INTERPRETER_H
#define TOKEN_INTERPRETER_H
#include <stdexcept>
#include "Tree_Construct_Record.h"

enum TOKEN_TYPE {COMMENT, CONNECTOR, ARGUMENT, COMMAND};
#define COMMENT_CHAR '#'

#ifndef CONNECTOR_TYPES
#define CONNECTOR_TYPES
//NOTE: connectors in the array and set need to have matching order
#define CONNECTOR_NUM 3
static const std::string CONNECTORS[CONNECTOR_NUM] = {"&&", "||", ";"};
enum CONNECT_TYPE {AND, OR, END};
#endif

class Token_Interpreter {
  private: 
    char*        token;
    bool         closure_char;
  public:
                 Token_Interpreter(char*);
    TOKEN_TYPE   token_type(Tree_Construct_Record*) const;
    CONNECT_TYPE connect_type() const;
    bool         contains_closure_char() const;

  private:
    bool         is_comment() const;
    bool         is_connector() const;
    void         filter_closure_char();
 };

Token_Interpreter::Token_Interpreter(char* token) {
  this->token = token;
  
  //the reasoning for closure_char initially being set false is explained
  //in the method's definition
  this->closure_char = false;
  if (contains_closure_char()) {
    closure_char = true;
    filter_closure_char();
  }
}

TOKEN_TYPE Token_Interpreter::token_type(Tree_Construct_Record* record) const {
  if (is_comment()) 
    return COMMENT;
  else if (is_connector())
    return CONNECTOR;
  else if (record->pend_process_init)
    return ARGUMENT;
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


bool Token_Interpreter::is_comment() const {
  unsigned i = 0;
  while (this->token[i] != '\0') {
    if (this->token[i] == COMMENT_CHAR)
      return true;
    i++;
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

void Token_Interpreter::filter_closure_char() {
  unsigned i;
  //get index of last char
  for (i = 0; this->token[i] != '\0'; i++) {}
    i--;
  this->token[i] = '\0';

  //FIXME: debug print
  std::cout << "closure char was filtered, token now: " << this->token << std::endl;
}
#endif
