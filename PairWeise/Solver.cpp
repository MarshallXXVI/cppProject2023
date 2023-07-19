#include "./Solver.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

// __________________________________________________________________
void Solver::getDataFromOption(std::vector<std::string> param) {
  int i = 1;
  while (param[i] != "\n") {
    option_.prozessor_.push_back(param[i]);
    i++;
  }
  i = i + 2;
  while (param[i] != "\n") {
    option_.ram_.push_back(param[i]);
    i++;
  }
  i = i + 2;
  while (i < (int)param.size()) {
    option_.bildschirm_.push_back(param[i]);
    i++;
  }
}

void Solver::getDataFromConstraint(std::vector<std::string> param) {
  for (int i = 0; i < (int)param.size(); i++) {
    std::string pro = "" ,ram = "", bild = "";
    while ((i < (int)param.size() - 1) && (param[i] != "\n" )) {
      if (param[i] == "Prozessor") {
        pro = param[i+1];
      }
      if (param[i] == "RAM") {
        ram = param[i+1];
      }
      if (param[i] == "Bildschirm") {
        bild = param[i+1];
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
  word = "Prozessor," + option_.prozessor_[i] + ",RAM," + option_.ram_[j] + ",Bildschirm," +
         option_.bildschirm_[k];
  return word;
}

// __________________________________________________________________
void Solver::generateModells() {
  std::ofstream tempFile("b.models");
  int i = 0;
  int j = 0;
  int k = 0;
  option_.prozessor_[i];
  option_.ram_[j];
  option_.bildschirm_[k];

  while (i < (int)option_.prozessor_.size() && j < (int)option_.ram_.size() &&
         k < (int)option_.bildschirm_.size()) {
    if (!ifMatchConstraints(i, j, k)) {
      tempFile << thisModellToString(i, j, k) << '\n';
      //std::cout << option_.prozessor_[i] << ":" << option_.ram_[j] << ":" << option_.bildschirm_[k] << std::endl;
    }
    //MyFile1 << thisModellToString(i, j, k) << '\n';
    if ((int)option_.prozessor_.size() > 1) {
      if (i == (int)option_.prozessor_.size() - 1 && k == (int)option_.bildschirm_.size() - 1) {
        i = 0;
        j++;
        k = 0;
        continue;
      }
    }
    k++;
    if (j < (int)option_.ram_.size()) {
      if (i == 0) {
        i = 1;
      } else {
        i = 0;
      }
      if ((int)option_.prozessor_.size() == 1) {
        i = 0;
        j++;
        if ((k < (int)option_.bildschirm_.size()) && (j > (int)option_.ram_.size())) {
          j = 0;
        }
      }
    }
    // std::cout << i << ":" << j << ":" << k << std::endl;
  }
  tempFile.close();
  std::ofstream MyFile2("a.models");
  MyFile2 << readAndTrimTrailingSpaces("b.models");
  MyFile2.close();
  std::filesystem::remove("b.models");

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
    if ((option_.prozessor_[i] == (constraints_[l].prozessor_) || constraints_[l].prozessor_ == "") && 
        (option_.ram_[j] == (constraints_[l].ram_) || constraints_[l].ram_ == "") && 
        (option_.bildschirm_[k] == (constraints_[l].bildschirm_) || constraints_[l].bildschirm_ == "")) {
      return true;
    }
  }
  return false;
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