//
// Created by ADMIN on 11-Oct-23.
//

#include "MyShell.hpp"
#include <readline/readline.h>
#include <readline/history.h>

std::vector<std::string> MyShell::readNext() {
  char * line;
  if((line = readline(promptPutter->put().c_str())) == NULL){
    std::cerr<< "MyShell::readNext: readline" << std::endl;
    delete[] line;
    throw std::exception();
  }
  
  if (line && *line)
    add_history (line);
  std::vector<std::string> argv;

  char* token;

  token=strtok(line," ");
  while (token!= NULL)
  {
    if(token[0] = '#'){
      break;
    }
    auto expanded = unfold_string(token);
    for(auto& s: expanded ){// should move the strings nice and easy
      argv.emplace_back(std::move(s));
    }
    token=strtok(NULL," ");
  }

  
  delete[] line;
  return argv;
}
