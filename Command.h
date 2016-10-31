#ifndef COMMAND_H
#define COMMAND_H

class Command{

  public:
    Command(){};
	
	  virtual void execute() = 0;
    virtual bool is_valid() = 0;
	
};

#endif