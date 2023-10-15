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

std::regex wildcardToRegex(const std::string& wildcard, bool caseSensitive)
{
    // Note It is possible to automate checking if filesystem is case sensitive or not (e.g. by performing a test first time this function is ran)
    std::string regexString{ wildcard };
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

    return std::regex(regexString, caseSensitive ? std::regex_constants::ECMAScript : std::regex_constants::icase);
}

bool wildmatch(const std::string& input, const std::string& wildcard)
{
    auto rgx = wildcardToRegex(wildcard);
    return std::regex_match(input, rgx);
}
static bool has_wildcards(const bfs::wpath & path){

}

/**
 * modifies s!
 * @param s
 * @return
 */
std::vector<std::string> unfold_string(char* s){
    //TODO підстановка вайлдкарлів
    //TODO

    // не всі стрінги це шлях
//  bfs::path(s);
// the wildcard substitution must occur before or after canonization of path?
// does nothing if no such file or directory returns the string
// if file ->wildcard sub
//iterate over path directories
// if any contain wildcard pattern -> seek and substitute
    const bfs::wpath path = s;
    const bfs::wpath &parent_path = path.parent_path();
    bool has_wildcard = has_wildcards(path.filename());

    boost::filesystem::wpath canonicalPath;
    try {

        if (path != ".." && path != ".") {

            if(has_wildcard){
                std::vector< std::string > matching_files;
                canonicalPath = boost::filesystem::canonical(parent_path);
                const auto &wildcard = path.filename().string();

                for (auto &&x: bfs::directory_iterator(canonicalPath)) {
                    if (wildmatch(x.path().filename().string(), wildcard))
                        matching_files.push_back(x.path().string());
                }
                return matching_files;
            }
            else{
                canonicalPath = boost::filesystem::canonical(s);
                return {canonicalPath.string()};
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return {s};

}
