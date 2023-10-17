//
// Created by ADMIN on 17-Oct-23.
//
#include <string>
#include <boost/filesystem/path.hpp>
#include <readline/history.h>
#include <iostream>

#include "HistorySaver.hpp"

HistorySaver::HistorySaver() {
  if(history_truncate_file(NULL, MAXLINES) || read_history(NULL)){
    std::cerr << "*** could not load history ***" << std::endl;
  };
}

HistorySaver::~HistorySaver() {
  if(write_history(NULL)){
    std::cerr << "*** could not save history ***" << std::endl;
  };
}