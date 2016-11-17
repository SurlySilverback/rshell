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
 
  //these singletons keep track of tree states and perform transitions
  Tree_Construct_Record* tree_record    = new Tree_Construct_Record(token_vector.size()); 
  Tree_Record_Updater*   record_updater = new Tree_Record_Updater(tree_record);
  
  //primary loop
  for (unsigned i = 0; i < token_vector.size(); i++) {
    Token_Interpreter token_interp(token_vector.at(i));        // 1.) create an interpreter, which gets details about current token     
    
    switch(token_interp.token_type(tree_record)) {             // 2.) invoke respective updater method based on type of token
      case COMMENT:
        record_updater->finalize_record();
        i = token_vector.size(); // terminate primary loop
        break;
      
      case CONNECTOR:
        record_updater->connect_update(token_vector.at(i));  
        if (token_interp.contains_closure_char())              // 3.) check for closure char; if found, finalize record and push tree root to line
          line.push_back(closure_handler(record_updater));  
        break;
      
      case COMMAND:
        record_updater->process_update(token_vector.at(i)); 
        if (token_interp.contains_closure_char())
          line.push_back(closure_handler(record_updater));          
        break;
      
      case ARGUMENT:
        record_updater->arg_update(token_vector.at(i));
        if (token_interp.contains_closure_char())
          line.push_back(closure_handler(record_updater)); 
        break;

      //FIXME: new cases
      case TEST:
        record_updater->test_update();
        break;
      case PRECEDE_CHAR:
        break;
    }
  }

  //FIXME: what if this closure_handler call was immediately preceded by another one? 
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

//this method is called at the end of line, or when encountering a semicolon delimiter,
//and completes instantiation of all pending record members, before clearing it
Command* Parser::closure_handler(Tree_Record_Updater* record_updater) {
  Command* root = record_updater->finalize_record();
  record_updater->reinit_record(token_vector.size());  
  
  return root;  
 }
#endif


