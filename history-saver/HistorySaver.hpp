//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_HISTORYSAVER_HPP
#define MYSHELL_HISTORYSAVER_HPP


#include <string>
#include <boost/filesystem/path.hpp>
#include <readline/history.h>
#include <iostream>

namespace HistorySaver {
  void load();
  void save();
};


#endif //MYSHELL_HISTORYSAVER_HPP
