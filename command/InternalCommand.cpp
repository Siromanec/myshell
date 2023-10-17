//
// Created by ADMIN on 11-Oct-23.
//

#include "InternalCommand.hpp"
#include "AbstractRunner.hpp"

void InternalCommand::execute() {
    if (getArgc() == 0) {
        AbstractRunner::merrno = internalCommands[":"](getArgc(), const_cast<char **>(getArgv()));
    }
    else {
        AbstractRunner::merrno = internalCommands[std::string(getArgv()[0])](getArgc(), const_cast<char **>(getArgv()));
    }
}