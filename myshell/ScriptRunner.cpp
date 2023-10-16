//
// Created by ADMIN on 11-Oct-23.
//

#include "ScriptRunner.hpp"

std::vector<std::string> ScriptRunner::readNext(bool &flag) {
    std::string line;
    std::vector<std::string> argv{};
    if(getline(scriptFile, line)){
        char* token;
        token=strtok(line.data()," ");
        while (token!= NULL)
        {
            if(token[0] == '#'){
                break;
            }
            auto expanded = unfold_string(token);
            for(auto& s: expanded ){// should move the strings nice and easy
                argv.emplace_back(std::move(s));
            }
            token=strtok(NULL," ");
        }
    }
    else {
        flag = false;
    }
    return argv;
}