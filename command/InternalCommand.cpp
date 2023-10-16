//
// Created by ADMIN on 11-Oct-23.
//

#include "InternalCommand.hpp"

void InternalCommand::execute() {
    if (getArgc() == 0) {
        internalCommands[":"](getArgc(), const_cast<char **>(getArgv()));
    }
    else {
        internalCommands[std::string(getArgv()[0])](getArgc(), const_cast<char **>(getArgv()));
    }
}