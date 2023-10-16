//
// Created by ADMIN on 11-Oct-23.
//

#include "PromptPutter.hpp"
#include "boost/filesystem.hpp"

std::string PromptPutter::put() {
    std::string prompt = boost::filesystem::current_path().string() + " $ ";
    return prompt;
}