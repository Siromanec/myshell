//
// Created by ADMIN on 11-Oct-23.
//

#include "MyShell.hpp"
#include <readline/readline.h>
#include <readline/history.h>

#include <iostream>
#include <stdlib.h>
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;
/**
 * modifies s!
 * @param s
 * @return
 */
static void unfold_string(std::string& s){
  //TODO підстановка вайлдкарлів
  //TODO

  // не всі стрінги це шлях
//  bfs::path(s);
//  boost::filesystem::path canonicalPath = boost::filesystem::canonical(s, relativeTo);
//  if(s!=".." && s!="." && s!="..")
//  char *path = nullptr; // dynamic buffsize
//  realpath(s.c_str(), path);
//  s = path;
//  delete[] path;

}
std::vector<std::string> MyShell::readNext() {
  char * line;
  if((line = readline(promptPutter->put().c_str())) == NULL){
    std::cerr<< "MyShell::readNext: readline" << std::endl;
    throw std::exception();
  }
  
  if (line && *line)
    add_history (line);
//  std::string;
  std::vector<std::string> argv;

  char *p;

  p=strtok(line," ");
  while (p!= NULL)
  {
    argv.emplace_back(p);
    p=strtok(NULL," ");
  }
  for (auto& s: argv){
    unfold_string(s);
  }
  
  
  
  delete[] line;
  return argv;
}
