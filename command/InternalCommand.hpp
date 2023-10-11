//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_INTERNALCOMMAND_HPP
#define MYSHELL_INTERNALCOMMAND_HPP


#include "Command.hpp"
//TODO implement selection of functions

class InternalCommand: public Command {
public:
  using Command::Command;

  void execute() const override;
};


#endif //MYSHELL_INTERNALCOMMAND_HPP
