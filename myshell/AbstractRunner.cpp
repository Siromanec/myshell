//
// Created by ADMIN on 11-Oct-23.
//

#include <iostream>
#include <memory>
#include "AbstractRunner.hpp"
#include "InternalCommand.hpp"
#include "ExternalCommand.hpp"
#include "ScriptCommand.hpp"

void AbstractRunner::run() {
  while(true) {
    auto command = getNextCommand();
    if (command == nullptr){ //TODO check if unique ptr can be nullptr
      return;
    }
    command->execute();
  }
}

std::unique_ptr<Command> AbstractRunner::getNextCommand() {
  const auto commandArgv = readNext();
  
  switch (getCommandType(commandArgv)) {
    case INTERNAL:
      return std::make_unique<InternalCommand>(commandArgv);
    case EXTERNAL:
      return std::make_unique<ExternalCommand>(commandArgv);
    case SCRIPT:
      return std::make_unique<ScriptCommand>(commandArgv);
    default:
      std::cerr << "*** unknown command type" << std::endl;
      throw std::exception();
  }
}


