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
  // FIXME: Test cout
  //std::cout << "Parser Constructor: the input_line arg is " << input_line << std::endl;
  this->input_line = string_to_char(input_line);
  this->token_vector = tokenize();
  
  // FIXME: Test cout
  //std::cout << "Parser Constructor: after tokenize, token vector is ";
  for (unsigned i = 0; i < token_vector.size(); ++i){
  
      std::cout << token_vector[i];
  }
  std::cout << std::endl;
}

char* Parser::string_to_char(std::string input_line) const {
  //extra index for \0 to terminate string
  char* converted_string = new char[input_line.size() + 1];
  
  strcpy(converted_string, input_line.c_str());
  
  // FIXME: Test cout
  //std::cout << "Parser-> string_to_char(): the input_line arg is " << input_line << std::endl;
  //std::cout << "Parser-> string_to_char(): converted_string is ";
  for (char *test_p = converted_string; *test_p != '\0' ; ++test_p)
      std::cout << *test_p;
  
  std::cout << std::endl;
  
  return converted_string;
}

Line* Parser::parse() {
  std::vector<Command*> line;
  Line* new_line_object;
 
  //these singletons keep track of tree states and perform transitions
  Tree_Construct_Record* tree_record    = new Tree_Construct_Record(token_vector.size()); 
  Tree_Record_Updater*   record_updater = new Tree_Record_Updater(tree_record);

  //since NULL-checks are used
  for (unsigned i = 0; i < tree_record->arg_array_size; i++)
    tree_record->pend_process_args[i] = NULL;
  
  //primary loop
  for (unsigned i = 0; i < token_vector.size(); i++) {
    Token_Interpreter token_interp(token_vector.at(i));    
    
    switch(token_interp.token_type(tree_record)) {   
      case COMMENT:
        record_updater->finalize_record();
        i = token_vector.size(); //to escape loop
        break;
      
      case CONNECTOR:
        record_updater->connect_update(token_vector.at(i));
   
        if (token_interp.contains_closure_char()) {
          line.push_back(closure_handler(record_updater));
          record_updater->reinit_record(token_vector.size());
        }
        break;
      
      case COMMAND:
        record_updater->process_update(token_vector.at(i)); 

        if (token_interp.contains_closure_char()) {
          line.push_back(closure_handler(record_updater));          
          record_updater->reinit_record(token_vector.size());
        }
        break;
      
      case ARGUMENT:
        record_updater->arg_update(token_vector.at(i));
 
        if (token_interp.contains_closure_char()) {
          line.push_back(closure_handler(record_updater));   
          record_updater->reinit_record(token_vector.size());
        }
    }
  }
  line.push_back(closure_handler(record_updater)); 
  new_line_object = new Line(line);

  return new_line_object; 
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

Command* Parser::closure_handler(Tree_Record_Updater* record_updater) {
  //std::cout << "handling closure\n";

  Command* root = record_updater->finalize_record();
  record_updater->reinit_record(token_vector.size());  
  
  return root;  
 }
#endif


