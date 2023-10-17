//
// Created by ADMIN on 11-Oct-23.
//

#ifndef TEMPLATE_COMMAND_HPP
#define TEMPLATE_COMMAND_HPP


#include <string>
#include <vector>

enum CommandType {INTERNAL, EXTERNAL, SCRIPT} ;



class Command {
//  const std::vector<std::string> argv;
  std::vector<const char*> cstrings;
  const std::vector<std::string> argv;
  // i am saving this because of dangling pointers
public:
  explicit Command(std::vector<std::string> &&argv): argv{std::move(argv)} {
    for(const auto& string : this->argv)
      cstrings.push_back(string.c_str());
  }
  virtual const char** getArgv(){
    return cstrings.data();
  }
  virtual size_t getArgc(){
    return cstrings.size();
  }
  virtual ~Command() = default;
  virtual void execute() = 0;

};

CommandType getCommandType(const std::vector<std::string> & argv);


#endif //TEMPLATE_COMMAND_HPP
