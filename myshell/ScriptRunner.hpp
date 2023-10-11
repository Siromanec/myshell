//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_SCRIPTRUNNER_HPP
#define MYSHELL_SCRIPTRUNNER_HPP


#include "AbstractRunner.hpp"

class ScriptRunner: public AbstractRunner {
public:
  virtual std::vector<std::string> readNext() override; //TODO use file lines

};


#endif //MYSHELL_SCRIPTRUNNER_HPP
