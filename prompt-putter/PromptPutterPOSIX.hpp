//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_PROMPTPUTTERPOSIX_HPP
#define MYSHELL_PROMPTPUTTERPOSIX_HPP


#include "PromptPutter.hpp"

class PromptPutterPOSIX: public PromptPutter {
public:
  void put() override;
};


#endif //MYSHELL_PROMPTPUTTERPOSIX_HPP
