#ifndef COMMAND_H
#define COMMAND_H

class Command{

  public:
    Command(){};
    virtual bool execute() = 0;
    virtual void print() = 0;
};

#endif
