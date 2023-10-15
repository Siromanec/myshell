//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_SCRIPTRUNNER_HPP
#define MYSHELL_SCRIPTRUNNER_HPP


#include "AbstractRunner.hpp"
#include <filesystem>
#include <iostream>
#include "boost/filesystem.hpp"


class ScriptRunner: public AbstractRunner {
private:
    std::string scriptName;
    std::vector<std::string> scriptArguments;
public:
    ScriptRunner (size_t argc, char* argv[]) {
        boost::filesystem::path path = argv[0];
        if( std::filesystem::exists(argv[0]) && path.extension() == AbstractRunner::extension) {
            scriptName = argv[0];
        }
        else {
            std::cerr << argv[0] <<": No such file or directory" << std::endl;
            errno = -1;
            throw std::exception();
        }
        for (size_t i = 1; i < argc; ++i) {
            scriptArguments.emplace_back(argv[i]);
        }
    }
  virtual std::vector<std::string> readNext() override; //TODO use file lines
};


#endif //MYSHELL_SCRIPTRUNNER_HPP
