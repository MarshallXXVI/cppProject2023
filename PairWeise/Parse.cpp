#include "./Parse.hpp"
#include <fstream>
#include <iostream>
#include <stdio.h>

// __________________________________________________________________
void Parse::ReadDataFromFile(const std::string &filename1,
                             const std::string &filename2) {
  std::vector<std::string> tempVecFile2 = ReturnVectorOfWord(filename2);
  for (int i = 0; i < (int)tempVecFile2.size(); i++) {
    std::vector<std::string> tempConstraintsType;
    while ((i < (int)tempVecFile2.size()) && (tempVecFile2[i] != "\n")) {
      tempConstraintsType.push_back(tempVecFile2[i]);
      i++;
    }
    constraints_.push_back(tempConstraintsType);
  }

  std::vector<std::string> tempVecFile1 = ReturnVectorOfWord(filename1);
  for (int i = 0; i < (int)tempVecFile1.size(); i++) {
    std::vector<std::string> tempOptionType;
    while ((i < (int)tempVecFile1.size()) && (tempVecFile1[i] != "\n")) {
      tempOptionType.push_back(tempVecFile1[i]);
      i++;
    }
    options_.push_back(tempOptionType);
  }
}

// __________________________________________________________________
std::vector<std::vector<std::string>>
Parse::vectorTransform(std::vector<std::string> param) {
  std::vector<std::vector<std::string>> tempField;
  for (int i = 0; i < (int)param.size(); i++) {
    std::vector<std::string> tempConstraintsType;
    while ((i < (int)param.size()) && (param[i] != "\n")) {
      tempConstraintsType.push_back(param[i]);
      i++;
    }
    tempField.push_back(tempConstraintsType);
  }
  return tempField;
}

// __________________________________________________________________
std::vector<std::string>
Parse::ReturnVectorOfWord(const std::string &filename) {
  std::vector<std::string> tempVecString;
  std::ifstream thisFile(filename);
  char c;
  std::string word;
  while (thisFile.get(c)) {
    if (c == ',' || c == '\n') {
      tempVecString.push_back(word);
      if (c == '\n') {
        tempVecString.push_back("\n");
      }
      word = "";
      continue;
    } else {
      if (c != '\n') {
        word += c;
      }
    }
  }
  tempVecString.push_back(word);
  thisFile.close();
  return tempVecString;
}

// __________________________________________________________________
void Parse::PrettyPrinter() {
  std::ofstream MyFile1("a_Copy.options");
  for (int i = 0; i < (int)options_.size(); i++) {
    for (int j = 0; j < (int)options_[i].size(); j++) {
      if (j < (int)options_[i].size()) {
        if (j == (int)options_[i].size() - 1) {
          if (i == (int)options_.size() - 1 &&
              j == (int)options_[i].size() - 1) {
            MyFile1 << options_[i][j];
          } else {
            MyFile1 << options_[i][j] << std::endl;
          }
        } else {
          MyFile1 << options_[i][j] << ",";
        }
      }
    }
  }
  MyFile1.close();

  std::ofstream MyFile2("a_Copy.constraints");
  for (int i = 0; i < (int)constraints_.size(); i++) {
    for (int j = 0; j < (int)constraints_[i].size(); j++) {
      if (j < (int)constraints_[i].size()) {
        if (j == (int)constraints_[i].size() - 1) {
          if (i == (int)constraints_.size() - 1 &&
              j == (int)constraints_[i].size() - 1) {
            MyFile2 << constraints_[i][j];
          } else {
            MyFile2 << constraints_[i][j];
            MyFile2 << std::endl;
          }
        } else {
          MyFile2 << constraints_[i][j] << ",";
        }
      }
    }
  }
  MyFile2.close();
}
