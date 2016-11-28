#ifndef CD_H
#define CD_H
#include "Command.h"

class CD: public Command {
  char* path;
 
 public:
    CD(char* path) {
      this->path = path;
    }

    bool execute() {
      return true;
    }
};
#endif
