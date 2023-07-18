#ifndef SOLVER_H_
#define SOLVER_H_

#include <string>
#include <utility>
#include <vector>

struct constraint {
  std::string prozessor_, ram_, bildschirm_;
};

// Models with pr. membervariables.
class Solver {
  std::vector<std::string> prozessor_;
  std::vector<std::string> ram_;
  std::vector<std::string> bildschirm_;
  std::vector<constraint> constraints_;

public:
  // Adding the various parameters to the options.
  void getDataFromOption(std::vector<std::string> param);
  void getDataFromConstraint(std::vector<std::string> param);
  // Main logic for generating modells. Depending on coming UB might
  // have to be adjusted.
  void generateModells();

private:
  // Name is program. Converting Modell to string.
  std::string thisModellToString(int i, int j, int k);
  bool ifMatchConstraints(int i, int j, int k);
};
#endif // SOLVER_H_