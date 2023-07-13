#ifndef PARSE_H_
#define PARSE_H_

#include <string>
#include <utility>
#include <vector>

class Parse {
public:
  void ReadDataFromFile(const std::string &filename1,
                        const std::string &filename2);
  void PrettyPrinter();
  std::vector<std::string> getOptions() { return options_; }

private:
  std::vector<std::string> options_;
  std::vector<std::string> constraints_;
};
#endif // PARSE_H_