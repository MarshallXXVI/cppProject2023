#include "./Parse.hpp"
#include <fstream>
#include <iostream>

// __________________________________________________________________
void Parse::ReadDataFromFile(const std::string &filename1,
                             const std::string &filename2) {
  options_ = ReturnVectorOfWord(filename1);
  constraints_ = ReturnVectorOfWord(filename2);
}

// __________________________________________________________________
std::vector<std::string> Parse::ReturnVectorOfWord(const std::string &filename) {
  std::vector<std::string> tempVecString;
  std::ifstream thisFile(filename);
  char c;
  std::string word = "";
  while (thisFile.get(c)) {
    if (c == ',' || c == '\n') {
      tempVecString.push_back(word);
      if (c == '\n') {
        tempVecString.push_back("\n");
      }
      word = "";
      continue;
    } else {
      word += c;
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
    if (i == (int)(options_.size() - 1)) {
      // std::cout << options_[i];
      MyFile1 << options_[i];
    } else if (options_[i] == "\n") {
      // std::cout << options_[i];
      MyFile1 << options_[i];
    } else {
      // std::cout << options_[i] << ",";
      if (options_[i + 1] == "\n" && i < (int)options_.size() - 2) {
        MyFile1 << options_[i];
      } else {
        // std::cout << constraints_[i] << ",";
        MyFile1 << options_[i] << ",";
      }
    }
  }
  // std::cout << std::endl;
  MyFile1.close();

  std::ofstream MyFile2("a_Copy.constraints");
  // std::cout << constraints_.size();
  for (int i = 0; i < (int)constraints_.size(); i++) {
    // std::cout << constraints_[i] <<std::endl;
    if (i == (int)(constraints_.size() - 1)) {
      // std::cout << constraints_[i];
      MyFile2 << constraints_[i];
    } else if (constraints_[i] == "\n") {
      // std::cout << constraints_[i];
      MyFile2 << constraints_[i];
    } else {
      if (constraints_[i + 1] == "\n" && i < (int)constraints_.size() - 2) {
        MyFile2 << constraints_[i];
      } else {
        // std::cout << constraints_[i] << ",";
        MyFile2 << constraints_[i] << ",";
      }
    }
  }
  // std::cout << std::endl;
  MyFile2.close();
}
