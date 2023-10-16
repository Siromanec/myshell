#ifndef MYSHELL_PROMPTPUTTERPOSIX_HPP
#define MYSHELL_PROMPTPUTTERPOSIX_HPP

#include <string>

class PromptPutter {
private:
    std::string buff;
public:
    PromptPutter(){
        buff.resize(100);
    }
    std::string put();
};

#endif //MYSHELL_PROMPTPUTTERPOSIX_HPP

