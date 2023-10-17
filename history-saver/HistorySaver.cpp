//
// Created by ADMIN on 17-Oct-23.
//
#include <string>
#include <boost/filesystem/path.hpp>
#include <readline/history.h>
#include <iostream>
#include <fstream>

#include "HistorySaver.hpp"

HistorySaver::HistorySaver() {
  if(history_truncate_file(path.c_str(), MAXLINES) || read_history(path.c_str())){
    std::cerr << "*** could not truncate or load history ***" << std::endl;
  }
}

HistorySaver::~HistorySaver() {
  if(write_history(path.c_str())){
    std::cerr << "*** could not save history ***" << std::endl;
  };
}
const std::string HistorySaver::path{"~/.msh_history"};