#ifndef PARSE_H_
#define PARSE_H_

#include <string>
#include <utility>
#include <vector>

// Main class for UB 11.
class Parse {
public:
  // method for parsing characterwise through .-files. Obviously looking
  // for "," and "\n" charachters as separators.
  void ReadDataFromFile(const std::string &filename1,
                        const std::string &filename2);
  // Pretty printer, creating the two copy files for .options and
  // .constraints. a_Copy.coptions & a_Copy.constraints.
  void PrettyPrinter();
  // getter function return field of options.
  std::vector<std::string> getOptions() { return options_; }
  // getter function return field of constraints.
  std::vector<std::string> getConstraints() { return constraints_; }
  // return vector of string as word also include '\n' aka endOfLine.
  std::vector<std::string> ReturnVectorOfWord(const std::string &filename);
private:
  std::vector<std::string> options_;
  std::vector<std::string> constraints_;
};
#endif // PARSE_H_