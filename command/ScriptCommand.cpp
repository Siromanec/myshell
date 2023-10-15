//
// Created by ADMIN on 11-Oct-23.
//

#include "ScriptCommand.hpp"
#include "ScriptRunner.hpp"

void ScriptCommand::execute() {
    auto* sr =new ScriptRunner(getArgc(), const_cast<char **>(getArgv()));
    sr->run();
}
