// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <memory>
#include "options_parser.h"
#include "MyShell.hpp"
#include "ScriptRunner.hpp"
#include "PromptPutter.hpp"

int main(int argc, char *argv[]) {
  std::unique_ptr<AbstractRunner> runner;
  if (argc == 1) {
    auto myshell = new MyShell();
    auto prompt_putter = std::make_unique<PromptPutter>();
    myshell->setPromptPutter(std::move(prompt_putter));
    runner = std::unique_ptr<AbstractRunner>(myshell);
  }
  else{
//TODO check if the argv[1] has extension ".msh" (defined in AbstractRunner) and pass the right arguments

    runner = std::make_unique<ScriptRunner>(argc-1, argv+1);
  }
  runner->run();
  return 0;
}
