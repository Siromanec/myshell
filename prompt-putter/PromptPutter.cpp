//
// Created by ADMIN on 11-Oct-23.
//

#include "PromptPutter.hpp"
#include "unistd.h"
#include <iostream>

std::string PromptPutter::put() {
    while(getcwd(buff.data(), buff.size()) == NULL) {
        if (errno == ERANGE) {
            buff.resize(buff.size() * 2);
        } else {
            std::cerr << "Cannot get current directory" << std::endl;
            throw std::exception();
        }
    }
    return buff;
}