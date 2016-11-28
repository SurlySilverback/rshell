//*********************
//TREE_CONSTRUCT_RECORD
//*********************
// -tracks all objects pending initialization and their arguments
// -pointers to the tree being built for the current line
// -can simply be referenced by any object used for parsing and tree construction
//  so that the respective object can act according to the state of the tree  

#ifndef TREE_CONSTRUCT_RECORD_H
#define TREE_CONSTRUCT_RECORD_H
#include <stddef.h>

//fwd decl
class Command;

#ifndef CONNECTOR_TYPES
#define CONNECTOR_TYPES
//NOTE: connectors in the array and set need to have matching order
#define CONNECTOR_NUM 3
static const std::string CONNECTORS[CONNECTOR_NUM] = {"&&", "||", ";"};
enum CONNECT_TYPE {AND, OR, END};
#endif

struct Tree_Construct_Record {  
  Command*               root;
  Command*               l_child;  
  Command*               r_child;    

  bool                   pend_connect_init;
  bool                   pend_process_init;
  bool                   pend_dir_change;

  char*                  pend_process_name;  
  CONNECT_TYPE*          pend_connect_type;

  bool                   pend_test_init;
  bool                   pend_preced_op;

  unsigned               pend_arg_num;
  int                    arg_array_size;
  char**                 pend_args;

  Tree_Construct_Record* child_record; 
  Tree_Construct_Record* parent_record;

  //note the default parent argument, because root records will have no parent
  Tree_Construct_Record(int arg_array_size, Tree_Construct_Record* parent = NULL): 
    root(NULL), 
    l_child(NULL), 
    r_child(NULL),
    pend_connect_init(false),
    pend_process_init(false),  
    pend_dir_change(false),
    pend_process_name(NULL), 
    pend_connect_type(NULL),
    pend_arg_num(0),
    arg_array_size(arg_array_size),
    pend_args(new char*[arg_array_size]),
    pend_test_init(false),
    pend_preced_op(false), 
    child_record(NULL),
    parent_record(parent)
  {
    //since NULL-checks are used, set every element
    for (int i = 0; i < this->arg_array_size; i++)
      this->pend_args[i] = NULL;
  };

  ~Tree_Construct_Record() {
    if (this->pend_connect_type != NULL)
      delete this->pend_connect_type;
  }
};
#endif
