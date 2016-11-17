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
    void     precede_char_update();
    
    Command* finalize_record();
    void     reinit_record(int token_size);     
  private:
    void     create_process();
    void     create_connect();
    void     create_test_process();
    void     reset_pend_process_records();
};

Tree_Record_Updater::Tree_Record_Updater(Tree_Construct_Record* record) {
  this->tree_record = record;
}

void Tree_Record_Updater::connect_update(char* new_connect) {  
  //when a connector is parsed, the arguments for processes and tests have been determined, and they are ready to be instantiated
  if (tree_record->pend_process_init)
    create_process();  
  else if (tree_record->pend_test_init)
    create_test_process();

  //if there is a pending connector, it's second child will have just been instantiated above, and this connector is ready to be created 
  if (tree_record->pend_connect_init)   
    create_connect();

  //update record with new connector
  Token_Interpreter new_connect_interpreter(new_connect);
  CONNECT_TYPE* new_connect_type = new CONNECT_TYPE((new_connect_interpreter.connect_type()));
  tree_record->pend_connect_type = new_connect_type;
  tree_record->pend_connect_init = true;
}

void Tree_Record_Updater::process_update(char* process_name) {
  tree_record->pend_process_name = process_name;
  tree_record->pend_process_init = true;      
}

void Tree_Record_Updater::arg_update(char* arg) {
  tree_record->pend_args[tree_record->pend_arg_num] = arg; 
  tree_record->pend_arg_num = (tree_record->pend_arg_num + 1);
}

void Tree_Record_Updater::test_update() {
  //this branch is necessary because parsing '[' and ']' both result in this method being called
  if (tree_record->pend_test_init) {
    create_test_process(); 
    return;
  }    
  tree_record->pend_test_init = true;
}

//called after end of parse or semi colon, instantiates all pending and returns root node of tree
Command* Tree_Record_Updater::finalize_record() {
  if (tree_record->pend_process_init)
    create_process(); 
  else if (tree_record->pend_test_init)
    test_update();
  
  if (tree_record->pend_connect_init)
    create_connect(); 
   
  tree_record->root = tree_record->l_child;
  return tree_record->root;
}

void Tree_Record_Updater::create_process() {
  Process* new_process = new Process(tree_record->pend_process_name, tree_record->pend_args);
  reset_pend_process_records();
    
  if (tree_record->l_child == NULL)
    tree_record->l_child = new_process;
  else
    tree_record->r_child = new_process;
}

void Tree_Record_Updater::create_connect() {  
  Command* connector; 
  CONNECT_TYPE pending_type = *(tree_record->pend_connect_type); 
  
  switch(pending_type) {
    case AND:
      connector = new And(tree_record->l_child, tree_record->r_child);
      break;

    case OR:
      connector = new Or(tree_record->l_child, tree_record->r_child);
      break;

    case END:
      break;
  }
  delete tree_record->pend_connect_type;  
  tree_record->l_child = connector;
  tree_record->r_child = NULL;
  tree_record->pend_connect_init = false;
}

void Tree_Record_Updater::create_test_process() {
  TestProcess* new_test;
  
  //use appropriate constructor based on whether there is an explicit flag argument  
  if (tree_record->pend_args[1] == NULL)
    new_test = new TestProcess(tree_record->pend_args[0]);
  else 
    new_test = new TestProcess(tree_record->pend_args[0], tree_record->pend_args[1]); 

  if (tree_record->l_child == NULL)
    tree_record->l_child = new_test;
  else
    tree_record->r_child = new_test;

  reset_pend_process_records();
}

void Tree_Record_Updater::reinit_record(int token_size) {
  delete tree_record;
  tree_record = new Tree_Construct_Record(token_size); 
}

//used to reset data members associated with pending processes 
void Tree_Record_Updater::reset_pend_process_records() {
  tree_record->pend_process_init = false;
  tree_record->pend_test_init = false;
  tree_record->pend_args = new char*[tree_record->arg_array_size];
  tree_record->pend_arg_num = 0;
   
  for (unsigned i = 0; i < tree_record->arg_array_size; i++)
    tree_record->pend_args[i] = NULL;
}
#endif
