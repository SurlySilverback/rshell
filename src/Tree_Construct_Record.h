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
  Tree_Construct_Record(int arg_array_size): 
    root(NULL), 
    l_child(NULL), 
    r_child(NULL),
    pend_connect_init(false),
    pend_process_init(false),  
    pend_process_name(NULL), 
    pend_connect_type(NULL),
    pend_arg_num(0),
    arg_array_size(arg_array_size),
    pend_process_args(new char*[arg_array_size])
  {};

  ~Tree_Construct_Record() {}

  Command*      root;
  Command*      l_child;  
  Command*      r_child;    

  bool          pend_connect_init;
  bool          pend_process_init;

  char*         pend_process_name;  
  CONNECT_TYPE* pend_connect_type;

  unsigned      pend_arg_num;
  int           arg_array_size;
  char**        pend_process_args;
};
#endif
