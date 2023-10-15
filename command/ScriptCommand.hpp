//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_SCRIPTCOMMAND_HPP
#define MYSHELL_SCRIPTCOMMAND_HPP


#include "Command.hpp"

class ScriptCommand: public Command {
public:
  using Command::Command; //TODO rewrite for diffirend constructor (or maybe not) (myshell ./.msh vs ./.msh)

  void execute() override;

};


#endif //MYSHELL_SCRIPTCOMMAND_HPP
