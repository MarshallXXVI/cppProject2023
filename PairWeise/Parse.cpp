#include "./Parse.hpp"
#include <fstream>
#include <iostream>
#include <stdio.h>

/// if the input file is not sorted. case 1.
/// sorted vector of int.

// __________________________________________________________________
void Parse::ReadDataFromFile(const std::string &filename1,
                             const std::string &filename2) {
    std::vector<std::string> tempVecFile2 = ReturnVectorOfWord(filename2);
    for (int i = 0; i < (int)tempVecFile2.size(); i++) {
      std::vector<std::string> tempConstraintsType;
      while((i < (int)tempVecFile2.size()) && (tempVecFile2[i] != "\n")) {
        std::cout << tempVecFile2[i].c_str() << " has size of :" <<tempVecFile2[i].size() << std::endl;
        tempConstraintsType.push_back(tempVecFile2[i]);
        i++;
      }
      constraints_.push_back(tempConstraintsType);
    }

    std::vector<std::string> tempVecFile1 = ReturnVectorOfWord(filename1);
    for (int i = 0; i < (int)tempVecFile1.size(); i++) {
      std::vector<std::string> tempOptionType;
      while((i < (int)tempVecFile1.size()) && (tempVecFile1[i] != "\n")) {
        std::cout << tempVecFile1[i].c_str() << " has size of :" <<tempVecFile1[i].size() << std::endl;
        tempOptionType.push_back(tempVecFile1[i]);
        i++;
      }
      options_.push_back(tempOptionType);
    }
   
}

// __________________________________________________________________
std::vector<std::string> Parse::ReturnVectorOfWord(const std::string &filename) {
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
        //std::cout << c << std::endl;
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
    for (int j = 0; j <(int)options_[i].size(); j++) {
      if (j < (int)options_[i].size()) {
        if (j == (int)options_[i].size() - 1) {
          if (i == (int)options_.size() - 1 && j == (int)options_[i].size() - 1) {
          //std::cout << options_[i][j];
          MyFile1 << options_[i][j];
          } else {
          //std::cout << options_[i][j] << std::endl;
          MyFile1 << options_[i][j] << std::endl;
          }
        } else {
          //std::cout << options_[i][j] << ",";
          MyFile1 << options_[i][j]<< ",";
        }
      }
    }
  }     
  MyFile1.close();

  std::ofstream MyFile2("a_Copy.constraints");
  for (int i = 0; i < (int)constraints_.size(); i++) {
    for (int j = 0; j <(int)constraints_[i].size(); j++) {
      if (j < (int)constraints_[i].size()) {
        if (j == (int)constraints_[i].size() - 1) {
          //std::cout << constraints_[i][j].size() << std::endl;
          if (i == (int)constraints_.size() - 1 && j == (int)constraints_[i].size() - 1) {
          //std::cout << constraints_[i][j];
          MyFile2 << constraints_[i][j];
          } else {
          MyFile2 << constraints_[i][j];
          MyFile2 << std::endl;
          }
        } else {
          //std::cout << constraints_[i][j] << ",";
          MyFile2 << constraints_[i][j] << ",";
        }
      }
    }
  }
  MyFile2.close();
}
