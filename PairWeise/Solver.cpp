#include "./Solver.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

// __________________________________________________________________
void Solver::getDataFromOption(std::vector<std::vector<std::string>> param) {
  optionCopy_ = param;
}

void Solver::getDataFromConstraint(std::vector<std::vector<std::string>> param) {
  constraintsCopy_ = param;
}

// __________________________________________________________________
void Solver::generateModells() {

}

// __________________________________________________________________
void Solver::generatePair() {
  for (int i = 0; i < optionCopy_.size(); i++) {
    std::vector<Pair> tempVecPair;
    for (int j = 1; j < optionCopy_[i].size(); j++) {
      Pair tempPair = {optionCopy_[i][0], optionCopy_[i][j]};
      tempVecPair.push_back(tempPair);
    }
    Pair_.push_back(tempVecPair);
  }

  for (int i = 0; i < Pair_.size(); i++) {
    for (int j = 0; j < Pair_[i].size(); j++) {
      std::cout << "(" << Pair_[i][j].Option_ << "," << Pair_[i][j].Value_ << ")" << std::endl;
    }
  }
}

// __________________________________________________________________
bool Solver::ifMatchConstraints(int i, int j, int k) {
  //std::cout << constraints_.size() << std::endl;
  // Check if empty a.constraints.
  // if (constraints_.size() == 1 &&
  //     constraints_[0].prozessor_ == "" &&
  //     constraints_[0].ram_ == "" &&
  //     constraints_[0].bildschirm_ == "") {
  //   return false;
  // }
  // for (int l = 0; l < (int)constraints_.size(); l++) {
  //   //std::cout << constraints_[l].prozessor_ << ":" << constraints_[l].ram_ << ":" << constraints_[l].bildschirm_ << std::endl;
  //   if ((option_.prozessor_[i] == (constraints_[l].prozessor_) || constraints_[l].prozessor_ == "") && 
  //       (option_.ram_[j] == (constraints_[l].ram_) || constraints_[l].ram_ == "") && 
  //       (option_.bildschirm_[k] == (constraints_[l].bildschirm_) || constraints_[l].bildschirm_ == "")) {
  //     return true;
  //   }
  // }
  // return false;
}

// __________________________________________________________________
std::string Solver::readAndTrimTrailingSpaces(std::string const & file)
{
    std::ifstream thisFile(file);
    std::string   buffer(std::istreambuf_iterator<char>{thisFile}, {});

    while (!buffer.empty() && std::isspace(buffer.back()))
        buffer.pop_back();

    return buffer;
}