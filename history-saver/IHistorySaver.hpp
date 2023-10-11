//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_IHISTORYSAVER_HPP
#define MYSHELL_IHISTORYSAVER_HPP


#include <string>

class IHistorySaver {
public:
  virtual void save(const std::string& commandText){};
  virtual const std::string& getNext(){};
  virtual const std::string& getPrevious(){};


};


#endif //MYSHELL_IHISTORYSAVER_HPP
