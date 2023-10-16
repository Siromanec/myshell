//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_INTERNALCOMMAND_HPP
#define MYSHELL_INTERNALCOMMAND_HPP


#include "Command.hpp"
#include "unordered_map"
#include "internal_commands-POSIX.hpp"
//TODO implement selection of functions

class InternalCommand: public Command {
private:
    std::unordered_map<std::string, std::function<int (int, char **)>> internalCommands = {
            {"merrno", &merrno},
            {"mpwd", &mpwd},
            {"mcd", &mcd},
            {"mexit", &mexit},
            {"mecho", &mecho},
            {"mexport", &mexport},
            {".", &mdot_command},
            {":", &mdummy_command}};
public:
  using Command::Command;

  void execute() override;
};


#endif //MYSHELL_INTERNALCOMMAND_HPP
