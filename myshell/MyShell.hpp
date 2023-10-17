//
// Created by ADMIN on 11-Oct-23.
//

#ifndef MYSHELL_MYSHELL_HPP
#define MYSHELL_MYSHELL_HPP


#include "AbstractRunner.hpp"
#include "PromptPutter.hpp"
#include "HistorySaver.hpp"

class MyShell: public AbstractRunner {
  std::unique_ptr<PromptPutter> promptPutter;
public:
  //TODO розібратися, як працює бібліотека "readline"; огорнути її в клас-адаптер (можливо, не один), якщо для вінди (mingw) цієї ліби нема, або є подібна з іншим інтерфейсом
  virtual std::vector<std::string> readNext(bool &flag) override; //TODO use userinput
  MyShell();

  void setPromptPutter(std::unique_ptr<PromptPutter>&& putter) {
    promptPutter = std::move(putter);
  }

};


#endif //MYSHELL_MYSHELL_HPP
