//
// Created by ADMIN on 11-Oct-23.
//

#ifndef TEMPLATE_ABSTRACTMYSHELL_HPP
#define TEMPLATE_ABSTRACTMYSHELL_HPP


#include <memory>
#include "Command.hpp"

//TODO добавити парсинг стрічки на окремі слова
class AbstractRunner {
public:
  static const std::vector<std::string> internal_commands;
  static const std::string name;
  static const std::string extension;


  virtual void run();

  virtual std::unique_ptr<Command> getNextCommand();

  virtual std::vector<std::string> readNext() = 0;

  virtual ~AbstractRunner() = default;
};

const std::vector<std::string> AbstractRunner::internal_commands{
    "merrno",
    "mpwd",
    "mcd",
    "mexit",
    "mecho",
    "mexport",
    ".",
};

const std::string AbstractRunner::name{"myshell"};
const std::string AbstractRunner::extension{".msh"};


#endif //TEMPLATE_ABSTRACTMYSHELL_HPP
