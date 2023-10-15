//
// Created by ADMIN on 11-Oct-23.
//

#ifndef TEMPLATE_ABSTRACTMYSHELL_HPP
#define TEMPLATE_ABSTRACTMYSHELL_HPP


#include <memory>
#include "Command.hpp"

#include <iostream>
#include <boost/filesystem.hpp>
#include <regex>

namespace bfs = boost::filesystem;

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

std::regex wildcardToRegex(const std::string& wildcard, bool caseSensitive = true);
bool wildmatch(const std::string& input, const std::string& wildcard);
static bool has_wildcards(const bfs::wpath & path);
std::vector<std::string> unfold_string(char* s);

#endif //TEMPLATE_ABSTRACTMYSHELL_HPP
