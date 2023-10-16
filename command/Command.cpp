//
// Created by ADMIN on 11-Oct-23.
//
#include <filesystem> // C++17
#include <boost/filesystem.hpp>

#include "Command.hpp"
#include "AbstractRunner.hpp"
namespace fs = std::filesystem;


CommandType getCommandType(const std::vector<std::string> &argv) {
  if (argv.size() == 0)
    return INTERNAL;
  const auto &commandName = argv[0];
//  if (commandName == AbstractRunner::name)
//    return SCRIPT;
// commented because it would prevent from starting myshell as subprocess
// so lets consider myshell command "external"
  for(const auto& c: AbstractRunner::internal_commands){
    if(c == commandName) {
      return INTERNAL;
    }
  }
  if (boost::filesystem::extension(commandName) == AbstractRunner::extension) //TODO should i check for "./"?
    return SCRIPT;

  return EXTERNAL;
}
