#include "./Solver.hpp"
#include <fstream>
#include <iostream>
#include <string>

// __________________________________________________________________
void Solver::getDataFromOption(std::vector<std::string> param) {
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

void Solver::getDataFromConstraint(std::vector<std::string> param) {
  for (int i = 0; i < (int)param.size(); i++) {
    std::string pro = "" ,ram = "", bild = "";
    while (param[i] != "\n" && i < ((int)param.size() - 1)) {
      if (param[i] == "Prozessor") {
        pro = param[i + 1];
      }
      if (param[i] == "RAM") {
        ram = param[i + 1];
      }
      if (param[i] == "Bildschirm") {
        bild = param[i + 1];
      }
      i = i + 2;
    }
    constraint tempCon = {pro, ram, bild};
    constraints_.push_back(tempCon);
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
    if (!ifMatchConstraints(i, j, k)) {
      MyFile1 << thisModellToString(i, j, k) << '\n';
      std::cout << prozessor_[i] << ":" << ram_[j] << ":" << bildschirm_[k] << std::endl;
    }
    //MyFile1 << thisModellToString(i, j, k) << '\n';
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

// __________________________________________________________________
bool Solver::ifMatchConstraints(int i, int j, int k) {
  //std::cout << constraints_.size() << std::endl;
  // Check if empty a.constraints.
  if (constraints_.size() == 1 &&
      constraints_[0].prozessor_ == "" &&
      constraints_[0].ram_ == "" &&
      constraints_[0].bildschirm_ == "") {
    return false;
  }
  for (int l = 0; l < (int)constraints_.size(); l++) {
    //std::cout << constraints_[l].prozessor_ << ":" << constraints_[l].ram_ << ":" << constraints_[l].bildschirm_ << std::endl;
    if ((prozessor_[i] == (constraints_[l].prozessor_) || constraints_[l].prozessor_ == "") && 
        (ram_[j] == (constraints_[l].ram_) || constraints_[l].ram_ == "") && 
        (bildschirm_[k] == (constraints_[l].bildschirm_) || constraints_[l].bildschirm_ == "")) {
      return true;
    }
  }
  return false;
}