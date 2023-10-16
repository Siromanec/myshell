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
  bool flag = true;
  while (flag) {
    auto command = getNextCommand(flag);
    if (command == nullptr) { //TODO check if unique ptr can be nullptr
      return;
    }
    command->execute();
  }
}

std::unique_ptr<Command> AbstractRunner::getNextCommand(bool &flag) {
  auto commandArgv = readNext(flag);

#ifdef DEBUG
  std::cout<<"argv: ";
  for (const auto& s: commandArgv){
    std::cout<< s<<'\t';
  }
  std::cout<< std::endl;
#endif

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

std::regex wildcardToRegex(const std::string &wildcard, bool caseSensitive) {
  // Note It is possible to automate checking if filesystem is case sensitive or not (e.g. by performing a test first time this function is ran)
  std::string regexString{wildcard};
  // Escape all regex special chars:
  regexString = std::regex_replace(regexString, std::regex("\\\\"), "\\\\");
  regexString = std::regex_replace(regexString, std::regex("\\^"), "\\^");
  regexString = std::regex_replace(regexString, std::regex("\\."), "\\.");
  regexString = std::regex_replace(regexString, std::regex("\\$"), "\\$");
  regexString = std::regex_replace(regexString, std::regex("\\|"), "\\|");
  regexString = std::regex_replace(regexString, std::regex("\\("), "\\(");
  regexString = std::regex_replace(regexString, std::regex("\\)"), "\\)");
  regexString = std::regex_replace(regexString, std::regex("\\{"), "\\{");
  regexString = std::regex_replace(regexString, std::regex("\\{"), "\\}");
  regexString = std::regex_replace(regexString, std::regex("\\["), "\\[");
  regexString = std::regex_replace(regexString, std::regex("\\]"), "\\]");
  regexString = std::regex_replace(regexString, std::regex("\\+"), "\\+");
  regexString = std::regex_replace(regexString, std::regex("\\/"), "\\/");
  // Convert wildcard specific chars '*?' to their regex equivalents:
  regexString = std::regex_replace(regexString, std::regex("\\?"), ".");
  regexString = std::regex_replace(regexString, std::regex("\\*"), ".*");

#ifdef DEBUG
  std::cerr << regexString << std::endl;
#endif
  return std::regex(regexString, caseSensitive ? std::regex_constants::ECMAScript : std::regex_constants::icase);
}

bool wildmatch(const std::string &input, const std::string &wildcard) {
  auto rgx = wildcardToRegex(wildcard);
  return std::regex_match(input, rgx);
}

static bool has_wildcards(const bfs::wpath &path) {

  for (char i: path.string()) {
    switch (i) {
      case '*':
        return true;
      case '?':
        return true;
      case '[': //TODO posible bug here
        return true;
    }
  }


  return false;
}

std::vector<std::string> unfold_string(char *s) {

#ifdef DEBUG
  std::cout << s << std::endl;
#endif

  if (has_wildcards(s)) {
    std::vector<std::string> matching_files;

    const bfs::wpath path{s};
    auto canonicalPath = boost::filesystem::canonical(path.parent_path());
    const auto wildcard = path.filename().string(); //using reference gives unexpected output (it changes with each call to filename().string())

    for (const auto& x: bfs::directory_iterator(canonicalPath)) {
      if (wildmatch(x.path().filename().string(), wildcard))
        matching_files.push_back(x.path().filename().string());
    }

    if(!matching_files.empty())
      return matching_files;
  }

  /*catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
  }*/
  return {s};

}
