#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include <iostream>
#include "Tree_Construct_Record.h"
#include "Token_Interpreter.h"
#include "Tree_Record_Updater.h"
#include "Process.h"

//FWD decls
class Line;

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

  //Line* current_line
  std::vector<Command*> line; //temp version
 
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

        //append current_line with record->root  
        i = token_vector.size();
        break;
      
      case CONNECTOR:
        std::cout << "CONNECTOR: " << token_vector.at(i) << std::endl; 
        record_updater->connect_update(token_vector.at(i));
   
        if (token_interp.contains_closure_char()) {
          //append current_line w/ closure_handler(record_updater);
          line.push_back(closure_handler(record_updater)); //alt vector test version

          record_updater->reinit_record(token_vector.size());
        }
        break;
      
      case COMMAND:
        std::cout << "COMMAND: " << token_vector.at(i) << std::endl;
        record_updater->process_update(token_vector.at(i)); 

        if (token_interp.contains_closure_char()) {
          //append current_line w/ closure_handler(record_updater);
          line.push_back(closure_handler(record_updater)); //alt vector test version
          
          record_updater->reinit_record(token_vector.size());
        }
        break;
      
      case ARGUMENT:
        std::cout << "ARG: " << token_vector.at(i) << std::endl;
        record_updater->arg_update(token_vector.at(i));
 
        if (token_interp.contains_closure_char()) {
          //append current_line w/ closure_handler(record_updater);
          line.push_back(closure_handler(record_updater)); //alt vector test version     

          record_updater->reinit_record(token_vector.size());
        }
    }
  }
 
  //append current_line w/ closure_handler(record_updater); 
  line.push_back(closure_handler(record_updater)); //alt vector test version
 
  //FIXME: debug print
  std::cout << "printing line contents\n";

  for (unsigned i = 0; i < line.size(); i++) 
    line.at(i)->print(); 
  
  return NULL;
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
  Command* root = record_updater->finalize_record();
  record_updater->reinit_record(token_vector.size());  

  return root;  
 }
#endif


