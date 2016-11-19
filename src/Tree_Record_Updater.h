//*******************
//TREE_RECORD_UPDATER
//*******************
// -encapsulates the primary algorithms for constructing trees
// -primary works through the reference to tree_record
// -reinit_record() allows for useage as singleton

#ifndef TREE_RECORD_UPDATER_H
#define TREE_RECORD_UPDATER_H
#include "Tree_Construct_Record.h"
#include "Token_Interpreter.h"
#include "Process.h"
#include "TestProcess.h"
#include "And.h"
#include "Or.h"

//fwd declare
class Test;

class Tree_Record_Updater {
  private:
    Tree_Construct_Record* tree_record;
  public:
             Tree_Record_Updater(Tree_Construct_Record*);
    void     connect_update(char*);
    void     process_update(char*);
    void     arg_update(char*);
    void     test_update();
    void     precede_char_update(char, int);
    Command* finalize_record();
    void     reinit_record(int token_size); 

    Tree_Construct_Record* find_record_to_update() const;
    
  private:
    void                   create_process();
    void                   create_connect();
    void                   create_test_process();
    void                   create_preced_tree();
    void                   reset_pend_process_records();
};

Tree_Record_Updater::Tree_Record_Updater(Tree_Construct_Record* record) {
  this->tree_record = record;
}

//***************
//updater methods
//***************
void Tree_Record_Updater::connect_update(char* new_connect) {  
  Tree_Construct_Record* record_to_update = find_record_to_update();

  if (record_to_update->pend_process_init)
    create_process();  
  else if (record_to_update->pend_test_init) 
    create_test_process();

  if (record_to_update->pend_connect_init)   
    create_connect();

  //update record with new connector
  Token_Interpreter new_connect_interpreter(new_connect);
  CONNECT_TYPE* new_connect_type = new CONNECT_TYPE((new_connect_interpreter.connect_type()));
  record_to_update->pend_connect_type = new_connect_type;
  record_to_update->pend_connect_init = true;
}

void Tree_Record_Updater::process_update(char* process_name) {
  Tree_Construct_Record* record_to_update = find_record_to_update();

  record_to_update->pend_process_name = process_name;
  record_to_update->pend_process_init = true;      
}

void Tree_Record_Updater::arg_update(char* arg) {
  Tree_Construct_Record* record_to_update = find_record_to_update();

  record_to_update->pend_args[tree_record->pend_arg_num] = arg; 
  record_to_update->pend_arg_num = (tree_record->pend_arg_num + 1);
}

void Tree_Record_Updater::precede_char_update(char precede_char, signed array_count) {
  Tree_Construct_Record* record_to_update = find_record_to_update();
  if (record_to_update == this->tree_record)
    std::cout << "record to update is root record\n";

  //construct new child record for youngest child
  if (precede_char == '(') {
    std::cout << "starting precedence tree, pend_preced == true and child_record instantiated\n"; 
    record_to_update->child_record = new Tree_Construct_Record(array_count, record_to_update);
    record_to_update->pend_preced_op = true;
  }
  else if (precede_char == ')')
    create_preced_tree();    
}

void Tree_Record_Updater::test_update() {
  Tree_Construct_Record* record_to_update = find_record_to_update();

  //this branch is necessary because parsing '[' and ']' both result in this method being called
  if (record_to_update->pend_test_init) {
    create_test_process(); 
    return;
  }    
  record_to_update->pend_test_init = true;
}

//***************
//creator methods
//***************

void Tree_Record_Updater::create_process() {
  Tree_Construct_Record* record_to_update = find_record_to_update();
  if (record_to_update == this->tree_record)
    std::cout << "process being created in root record\n";

  std::cout << "creating new process: " << record_to_update->pend_process_name << "\n";
  std::cout << record_to_update->pend_args[0] << std::endl;  

  Process* new_process = new Process(record_to_update->pend_process_name, record_to_update->pend_args);
  reset_pend_process_records();
    
  if (record_to_update->l_child == NULL)
    record_to_update->l_child = new_process;
  else
    record_to_update->r_child = new_process;
}

void Tree_Record_Updater::create_connect() { 
  std::cout << "creating connector\n"; 
  Tree_Construct_Record* record_to_update = find_record_to_update();

  Command* connector; 
  CONNECT_TYPE pending_type = *(record_to_update->pend_connect_type); 
  
  switch(pending_type) {
    case AND:
      connector = new And(record_to_update->l_child, record_to_update->r_child);
      break;

    case OR:
      connector = new Or(record_to_update->l_child, record_to_update->r_child);
      break;

    case END:
      break;
  }
  delete record_to_update->pend_connect_type;
  record_to_update->pend_connect_type = NULL;

  record_to_update->l_child = connector;
  record_to_update->r_child = NULL;
  record_to_update->pend_connect_init = false;
}

void Tree_Record_Updater::create_test_process() {
  Tree_Construct_Record* record_to_update = find_record_to_update();
  TestProcess* new_test;
  
  //use appropriate constructor based on whether there is an explicit flag argument  
  if (record_to_update->pend_args[1] == NULL)
    new_test = new TestProcess(record_to_update->pend_args[0]);
  else 
    new_test = new TestProcess(record_to_update->pend_args[0], record_to_update->pend_args[1]); 
 
  if (record_to_update->l_child == NULL)
    record_to_update->l_child = new_test;
  else
    record_to_update->r_child = new_test;

  reset_pend_process_records();
}

//finalize youngest child record and update parent with record's tree root
void Tree_Record_Updater::create_preced_tree() {
  Tree_Construct_Record* record_to_update = find_record_to_update();
   
  if (record_to_update->parent_record != NULL)
    record_to_update = record_to_update->parent_record;
  
  Command* root = finalize_record();

  if (record_to_update->child_record != NULL) {
    delete record_to_update->child_record; 
    record_to_update->child_record = NULL;
  }

  record_to_update->pend_preced_op = false;

  if (record_to_update->l_child == NULL)
    record_to_update->l_child = root;
  else
    record_to_update->r_child = root;
}

//******************************
//finalization and reset methods
//******************************

//called after end of parse or semi colon, instantiates all pending and returns root node of tree
//NOTE: if precedence operators are correctly entered, the record to finalize should be the root record
Command* Tree_Record_Updater::finalize_record() {
  Tree_Construct_Record* record_to_finalize = find_record_to_update();

  if (record_to_finalize->pend_process_init) {
    create_process();
  }
 
  else if (record_to_finalize->pend_test_init)
    test_update();
  
  if (record_to_finalize->pend_connect_init)
    create_connect(); 

  record_to_finalize->root = record_to_finalize->l_child;
  return record_to_finalize->root;
}

void Tree_Record_Updater::reinit_record(int token_size) {
  delete tree_record;
  tree_record = new Tree_Construct_Record(token_size); 
}

//used to reset data members associated with pending processes 
void Tree_Record_Updater::reset_pend_process_records() {
  Tree_Construct_Record* record_to_update = find_record_to_update();

  record_to_update->pend_process_init = false;
  record_to_update->pend_test_init = false;
  record_to_update->pend_args = new char*[tree_record->arg_array_size];
  record_to_update->pend_arg_num = 0;
   
  for (unsigned i = 0; i < record_to_update->arg_array_size; i++)
    record_to_update->pend_args[i] = NULL;
}

//*************
//misc. methods
//*************

//each update will need to determine the youngest record (to account for precede ops)
Tree_Construct_Record* Tree_Record_Updater::find_record_to_update() const {
  Tree_Construct_Record* current = this->tree_record;
  
  while (current->pend_preced_op) {
    current = current->child_record;
  }
 
  return current;
}

#endif
