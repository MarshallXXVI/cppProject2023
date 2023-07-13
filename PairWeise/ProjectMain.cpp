#include "./Parse.hpp"
#include "./Models.hpp"
#include <unistd.h>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
  // Parse the command-line arguments.
  if (argc != 3) {
    std::cout << "Usage: ./Main [file] [file]"
              << std::endl;
    std::exit(1);
  }

  std::string optionFile = argv[1];
  std::string constraintsFile = argv[2];

  Parse p;
  p.ReadDataFromFile(optionFile, constraintsFile);
  p.PrettyPrinter();
  Models m;
  m.getDataFromParse(p.getOptions());
  m.generateModells();

}