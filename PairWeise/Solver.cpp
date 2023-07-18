#include "./Solver.hpp"
#include <fstream>
#include <iostream>

// __________________________________________________________________
void Solver::getDataFromParse(std::vector<std::string> param) {
  int i = 1;
  while (param[i] != "\n") {
    prozessor_.push_back(param[i]);
    i++;
  }
  i = i + 2;
  while (param[i] != "\n") {
    ram_.push_back(param[i]);
    i++;
  }
  i = i + 2;
  while (i < (int)param.size()) {
    bildschirm_.push_back(param[i]);
    i++;
  }
}

// __________________________________________________________________
std::string Solver::thisModellToString(int i, int j, int k) {
  std::string word = "";
  word = "Prozessor," + prozessor_[i] + ",RAM," + ram_[j] + ",Bildschirm," +
         bildschirm_[k];
  return word;
}

// __________________________________________________________________
void Solver::generateModells() {
  std::ofstream MyFile1("a.models");
  int i = 0;
  int j = 0;
  int k = 0;
  prozessor_[i];
  ram_[j];
  bildschirm_[k];

  while (i < (int)prozessor_.size() && j < (int)ram_.size() &&
         k < (int)bildschirm_.size()) {
    // std::cout << thisModellToString(i, j, k) << std::endl;
    MyFile1 << thisModellToString(i, j, k) << '\n';
    if ((int)prozessor_.size() > 1) {
      if (i == (int)prozessor_.size() - 1 && k == (int)bildschirm_.size() - 1) {
        i = 0;
        j++;
        k = 0;
        continue;
      }
    }
    k++;
    if (j < (int)ram_.size()) {
      if (i == 0) {
        i = 1;
      } else {
        i = 0;
      }
      if ((int)prozessor_.size() == 1) {
        i = 0;
        j++;
        if ((k < (int)bildschirm_.size()) && (j > (int)ram_.size())) {
          j = 0;
        }
      }
    }
    // std::cout << i << ":" << j << ":" << k << std::endl;
  }
  MyFile1.close();
}