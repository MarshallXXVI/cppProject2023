#ifndef MODELL_H_
#define MODELL_H_

#include <string>
#include <utility>
#include <vector>

// Models with pr. membervariables.
class Models {
  std::vector<std::string> prozessor_;
  std::vector<std::string> ram_;
  std::vector<std::string> bildschirm_;

public:
  // Adding the various parameters to the options.
  void getDataFromParse(std::vector<std::string> param);
  // Main logic for generating modells. Depending on coming UB might
  // have to be adjusted.
  void generateModells();

private:
  // Name is program. Converting Modell to string.
  std::string thisModellToString(int i, int j, int k);
};
#endif // MODELL_H_