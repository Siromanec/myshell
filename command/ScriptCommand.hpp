//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_SCRIPTCOMMAND_HPP
#define MYSHELL_SCRIPTCOMMAND_HPP


#include "Command.hpp"
#include "ExternalCommand.hpp"

class ScriptCommand: public ExternalCommand {
public:
//  using ExternalCommand::ExternalCommand; //TODO rewrite for diffirend constructor (or maybe not) (myshell ./.msh vs ./.msh)
    explicit ScriptCommand(std::vector<std::string> &argv){
        cstrings.push_back( "myshell");
        for(const auto& string : argv)
            cstrings.push_back(string.c_str());
    }

  void execute() override;

};


#endif //MYSHELL_SCRIPTCOMMAND_HPP
