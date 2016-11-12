#ifndef TREE_RECORD_UPDATER_H
#define TREE_RECORD_UPDATER_H
#include "Tree_Construct_Record.h"
#include "Token_Interpreter.h"
#include "Process.h"
#include "And.h"
#include "Or.h"

class Tree_Record_Updater {
  private:
    Tree_Construct_Record* tree_record;
  public:
             Tree_Record_Updater(Tree_Construct_Record*);
    void     connect_update(char*);
    void     process_update(char*);
    void     arg_update(char*);
    Command* finalize_record();
    void     reinit_record(int token_size); 
  private:
    char*    filter_closure_char(char*);
    void     reset_pend_process_records();
};

Tree_Record_Updater::Tree_Record_Updater(Tree_Construct_Record* record) {
  this->tree_record = record;
}

void Tree_Record_Updater::connect_update(char* new_connect) {
  
  //create process from pending process and add to tree
  if (tree_record->pend_process_init) { 
    Process* new_process = new Process(tree_record->pend_process_name, tree_record->pend_process_args);
    reset_pend_process_records();
    
    if (tree_record->l_child == NULL)
      tree_record->l_child = new_process;
    else
      tree_record->r_child = new_process;
  }
     
  //note: if above 'else' branch executes, this branch must always execute 
  if (tree_record->pend_connect_init) {
    
    //create connector from pending connect and add to tree
    Command* connector = NULL; 
    CONNECT_TYPE pending_type = *(tree_record->pend_connect_type); 
  
    switch(pending_type) {
      case AND:
        connector = new And(tree_record->l_child, tree_record->r_child);
        break;

      case OR:
        connector = new Or(tree_record->l_child, tree_record->r_child);
        break;

      case END:
        std::cout << "placeholder\n";
    }
    tree_record->l_child = connector;
    tree_record->r_child = NULL;
  }

  //update pending connector type with new connector
  Token_Interpreter new_connect_interpreter(new_connect);

  CONNECT_TYPE* new_connect_type = NULL;
  new_connect_type = new CONNECT_TYPE((new_connect_interpreter.connect_type()));

  tree_record->pend_connect_type = new_connect_type;
  tree_record->pend_connect_init = true;
}

void Tree_Record_Updater::process_update(char* process_name) {
  tree_record->pend_process_name = process_name;
  tree_record->pend_process_init = true;      
}

void Tree_Record_Updater::arg_update(char* arg) {
  tree_record->pend_process_args[tree_record->pend_arg_num] = arg; 
  tree_record->pend_arg_num = (tree_record->pend_arg_num + 1);
}

//called after end of parse or semi colon, instantiates all pending and returns root node of tree
Command* Tree_Record_Updater::finalize_record() {
  if (tree_record->pend_process_init) {
    Process* new_process = new Process(tree_record->pend_process_name, tree_record->pend_process_args);
    reset_pend_process_records();
    
    if (tree_record->l_child == NULL)
      tree_record->l_child = new_process;
    else
      tree_record->r_child = new_process;
  }
  if (tree_record->pend_connect_init) {
    Command* connector = NULL; 
    CONNECT_TYPE pending_type = *(tree_record->pend_connect_type); 
  
    switch(pending_type) {
      case AND:
        connector = new And(tree_record->l_child, tree_record->r_child);
        break;
      case OR:
        connector = new Or(tree_record->l_child, tree_record->r_child);
        break;
      case END:
        std::cout << "placeholder\n";
    }
    tree_record->l_child = connector;
    tree_record->r_child = NULL;
    tree_record->pend_connect_init = false;
    tree_record->root = connector;
  }

  else if (tree_record->root == NULL) {
    tree_record->root = tree_record->l_child;
    tree_record->l_child = NULL;
  }

  //std::cout << "record finalized\n";
  return tree_record->root;
}

void Tree_Record_Updater::reinit_record(int token_size) {
  delete tree_record;
  tree_record = new Tree_Construct_Record(token_size); 
}

void Tree_Record_Updater::reset_pend_process_records() {
  tree_record->pend_process_init = false;
  tree_record->pend_process_args = new char*[tree_record->arg_array_size];
  tree_record->pend_arg_num = 0;
  
  for (unsigned i = 0; i < tree_record->arg_array_size; i++)
    tree_record->pend_process_args[i] = NULL;
}
#endif
