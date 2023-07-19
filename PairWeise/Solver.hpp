#ifndef SOLVER_H_
#define SOLVER_H_

#include <string>
#include <utility>
#include <vector>

struct constraint {
  std::string prozessor_, ram_, bildschirm_;
};

struct option {
  std::vector<std::string> prozessor_, ram_, bildschirm_;
};

// Models with pr. membervariables.
class Solver {
  option option_;
  std::vector<constraint> constraints_;

public:
  // Adding the various parameters to the options.
  void getDataFromOption(std::vector<std::string> param);
  // Adding the various set of constraints.
  void getDataFromConstraint(std::vector<std::string> param);
  // Main logic for generating modells. Depending on coming UB might
  // have to be adjusted.
  void generateModells();
  std::vector<constraint> getConstraint() { return constraints_; }
  option getOption() {return option_; }

private:
  // Name is program. Converting Modell to string.
  std::string thisModellToString(int i, int j, int k);
  // filtering function return true if model match one of constraints.
  bool ifMatchConstraints(int i, int j, int k);
  // eliminate trailing whitespaces (newlines).
  std::string readAndTrimTrailingSpaces(std::string const & file);
};
#endif // SOLVER_H_