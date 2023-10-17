#include "HistorySaver.hpp"
//#include <fstream>

int maxnlines = 64;
const std::string path{"~/.msh_history"};

void HistorySaver::load() {
  if(history_truncate_file(path.c_str(), maxnlines) || read_history(path.c_str())){
    std::cerr << "*** could not load history ***" << std::endl;
  }
}

void HistorySaver::save() {
  if(write_history(path.c_str())){
//    std::
    std::cerr << "*** could not save history ***" << std::endl;
  }
}
