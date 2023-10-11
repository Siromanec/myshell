//
// Created by ADMIN on 11-Oct-23.
//

#ifndef TEMPLATE_COMMAND_HPP
#define TEMPLATE_COMMAND_HPP


#include <string>
#include <vector>

enum CommandType {INTERNAL, EXTERNAL, SCRIPT} ;



class Command {
  const std::vector<std::string> argv;
public:
  explicit Command(std::vector<std::string> argv): argv{std::move(argv)}{
  }
  virtual ~Command() = default;
  virtual void execute() const = 0;


};

CommandType getCommandType(const std::vector<std::string> & argv);


#endif //TEMPLATE_COMMAND_HPP
