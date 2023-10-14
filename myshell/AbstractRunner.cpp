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
  auto commandArgv = readNext();
  
  switch (getCommandType(commandArgv)) {
    case INTERNAL:
      return std::make_unique<InternalCommand>(std::move(commandArgv));
    case EXTERNAL:
      return std::make_unique<ExternalCommand>(std::move(commandArgv));
    case SCRIPT:
      return std::make_unique<ScriptCommand>(std::move(commandArgv));
    default:
      std::cerr << "*** unknown command type" << std::endl;
      throw std::exception();
  }
}


