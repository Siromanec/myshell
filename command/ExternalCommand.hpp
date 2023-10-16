//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_EXTERNALCOMMAND_HPP
#define MYSHELL_EXTERNALCOMMAND_HPP


#include "Command.hpp"
#include <iostream>

//TODO implement fork/exec stuff
class ExternalCommand: public Command {
public:
  using Command::Command;

  void execute() override;
};


#endif //MYSHELL_EXTERNALCOMMAND_HPP
