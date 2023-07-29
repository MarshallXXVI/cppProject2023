#include "./Solver.hpp"
#include "./Parse.hpp"
#include "./Checker.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

// check if incoming file has eol if yes remove.
// and also check if a.constraints is empty.
int main(int argc, char **argv) {
  Checker c;
  Solver s;
  Parse p;
  // Parse the command-line arguments.
  if (argc != 4) {
    std::cout << "Usage: ./Main [file] [file] [file]" << std::endl;
    std::exit(1);
  }
  std::string optionFile = argv[1];
  std::string constraintsFile = argv[2];
  std::string modelsFile = argv[3];
  s.handleInputFiles(optionFile, constraintsFile);
  c.readDataInput(optionFile, constraintsFile);
  if (!c.ifOptionAndConstraints()) {
    return c.errorCode_;
  }
  p.ReadDataFromFile(optionFile, constraintsFile);
  p.PrettyPrinter();
  s.getDataFromOption(p.getOptions());
  s.getDataFromConstraint(p.getConstraints());
  s.generateModells();
}