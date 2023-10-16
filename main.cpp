// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "options_parser.h"
#include "MyShell.hpp"
#include "ScriptRunner.hpp"
#include "PromptPutter.hpp"

int main(int argc, char *argv[]) {
  std::unique_ptr<AbstractRunner> runner;
  if (argc == 1) {
    auto myshell = new MyShell();
    auto prompt_putter = std::unique_ptr<PromptPutter>(new PromptPutter());
    myshell->setPromptPutter(std::move(prompt_putter));
    runner = std::unique_ptr<AbstractRunner>(myshell);
  }
  else{
//TODO check if the argv[1] has extension ".msh" (defined in AbstractRunner) and pass the right arguments
    command_line_options_t command_line_options{argc, argv};
    std::cout << "A flag value: " << command_line_options.get_A_flag() << std::endl;
    runner = std::make_unique<ScriptRunner>(argc, argv);
  }
  runner->run();
  return 0;
}
