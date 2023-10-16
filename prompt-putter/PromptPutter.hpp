//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_PROMPTPUTTER_HPP
#define MYSHELL_PROMPTPUTTER_HPP

// with prompt putter we can control
// 1. system specific prompt
// 2. whether we should put it at all
#include <string>
class PromptPutter {

public:
  virtual std::string put() = 0;
};


#endif //MYSHELL_PROMPTPUTTER_HPP
