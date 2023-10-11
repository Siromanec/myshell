//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_HISTORYSAVERTOFILE_HPP
#define MYSHELL_HISTORYSAVERTOFILE_HPP

#include <filesystem>
#include <fstream>
#include <vector>
#include "IHistorySaver.hpp"

namespace fs = std::filesystem;

class HistorySaverToFile: public IHistorySaver {
  std::ofstream file;
  std::vector<std::string> history;
  HistorySaverToFile(const std::string & fpath) {
    file.open(fpath);

    //TODO load past commands into memmory
  }
  void save(const std::string &commandText) override {
    file << commandText << std::endl;
  }
  ~HistorySaverToFile() {
    file.close();
  }

//  fs::file
};


#endif //MYSHELL_HISTORYSAVERTOFILE_HPP
