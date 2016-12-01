#ifndef PARSER_H
#define PARSER_H
#include <string.h>
#include <vector>
#include <iostream>
#include "Tree_Construct_Record.h"
#include "Token_Interpreter.h"
#include "Tree_Record_Updater.h"
#include "Process.h"
#include "Line.h"

class Parser {
  private:
    char*              input_line;
    std::vector<char*> token_vector;
  public:
                       Parser(std::string);
    Line*              parse();
  private:
    char*              string_to_char(std::string) const; 
    std::vector<char*> tokenize() const;
    Command*           closure_handler(Tree_Record_Updater*);
    bool               post_token_handling_routine(Token_Interpreter*, Tree_Record_Updater*);
};

Parser::Parser(std::string input_line) {
  this->input_line = string_to_char(input_line);
  this->token_vector = tokenize();
}

char* Parser::string_to_char(std::string input_line) const {
  //extra index for \0 to terminate string
  char* converted_string = new char[input_line.size() + 1];
  strcpy(converted_string, input_line.c_str());  

  return converted_string;
}

Line* Parser::parse() {
  std::vector<Command*> line;
  Line* current_line;
 
  //these objects keep track of tree states and perform transitions
  Tree_Construct_Record* tree_record    = new Tree_Construct_Record(token_vector.size()); 
  Tree_Record_Updater*   record_updater = new Tree_Record_Updater(tree_record);
  
  //primary loop
  for (unsigned i = 0; i < token_vector.size(); i++) {
    if (static_cast<std::string>(token_vector.at(i)) == "exit" || static_cast<std::string>(token_vector.at(i)) == "Exit")
      exit(1);

    // 1.) create an interpreter, which gets details about current token 
    Token_Interpreter token_interp(token_vector.at(i));      
 
    // 2. before handling token type, determine if there is a flush opening preced op; if so, update record and replace token w/filtered version
    if (token_interp.check_flush_preced()) {
      this->token_vector.at(i) = token_interp.get_updated_token();
      if (token_interp.preced_char_type() == '(')
        record_updater->precede_char_update(token_interp.preced_char_type(), this->token_vector.size());
    }

    // 3.) invoke respective updater method based on type of token
    switch(token_interp.token_type(tree_record)) {             
      case COMMENT:
        record_updater->finalize_record();
        i = token_vector.size(); // terminate primary loop
        break;
      
      case CONNECTOR:
        record_updater->connect_update(token_vector.at(i));
  
        if (post_token_handling_routine(&token_interp, record_updater))  // 4.) post handling handles cases where semicolon or ')' was flush with the token
          line.push_back(closure_handler(record_updater));  
        break;
      
      case COMMAND:
        record_updater->process_update(token_vector.at(i)); 
        
        if (post_token_handling_routine(&token_interp, record_updater))
          line.push_back(closure_handler(record_updater));        
        break;
      
      case ARGUMENT:
        record_updater->arg_update(token_vector.at(i));
        
        if (post_token_handling_routine(&token_interp, record_updater))
          line.push_back(closure_handler(record_updater));  
        break;

      case TEST:
        record_updater->test_update();

        if (post_token_handling_routine(&token_interp, record_updater))
          line.push_back(closure_handler(record_updater));  
        break;

      case PRECEDE_CHAR:
        record_updater->precede_char_update(token_interp.preced_char_type(), this->token_vector.size());
       
        //post handling isn't invoked, since this branch is only for tokens which didn't have flush precedence chars 
        if (token_interp.contains_closure_char())
          line.push_back(closure_handler(record_updater));
        break;
  
      case DIR_CHANGE:
        record_updater->directory_update();

        if (post_token_handling_routine(&token_interp, record_updater))
          line.push_back(closure_handler(record_updater));  
        break;
    }
  }

  line.push_back(closure_handler(record_updater));
  current_line = new Line(line);

  return current_line; 
}

//convert string to vector of c-string tokens
std::vector<char*> Parser::tokenize() const {
  std::vector<char*> token_vector;
  char* current_token;  
  
  current_token = strtok(input_line, " ");
  while (current_token != NULL) {
    token_vector.push_back(current_token);
    current_token = strtok(NULL, " ");
  }    
  
  return token_vector; 
}

bool Parser::post_token_handling_routine(Token_Interpreter* interpreter, Tree_Record_Updater* updater) {
  if (interpreter->check_flush_preced()) {
    if (interpreter->preced_char_type() == ')') {
      
      //since there may several adjace closing preced ops, each one will require record update
      for (int i = 0; i < interpreter->get_adjace_preced_count(); i++)
        updater->precede_char_update(interpreter->preced_char_type(), this->token_vector.size());
    }
  }

  if (interpreter->contains_closure_char())
    return true;
  return false;
}

//this method is called at the end of line, or when encountering a semicolon delimiter,
//and completes instantiation of all pending record members, before clearing it
Command* Parser::closure_handler(Tree_Record_Updater* record_updater) {
  Command* root = record_updater->finalize_record();
  record_updater->reinit_record(token_vector.size());  
  
  return root;  
}
#endif


