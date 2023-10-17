//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_HISTORYSAVER_HPP
#define MYSHELL_HISTORYSAVER_HPP


#include <string>
#include <boost/filesystem/path.hpp>

class HistorySaver {
  boost::filesystem::wpath path;
public:
  HistorySaver();
  ~HistorySaver();

  virtual void save(){};

};


#endif //MYSHELL_HISTORYSAVER_HPP
