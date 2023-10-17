//
// Created by ADMIN on 11-Oct-23.
//

#include "ScriptCommand.hpp"
#include "ScriptRunner.hpp"
#include "AbstractRunner.hpp"
void ScriptCommand::execute() {
    ScriptRunner sr{getArgc(), const_cast<char **>(getArgv())};
    sr.run();
}

ScriptCommand::ScriptCommand(std::vector<std::string> &argv) {
  cstrings.emplace_back(AbstractRunner::name.c_str());
  for(const auto& string : argv)
    cstrings.push_back(string.c_str());
}
