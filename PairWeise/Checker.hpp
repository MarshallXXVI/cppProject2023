#ifndef CHECKER_H_
#define CHECKER_H_

#include <string>
#include <utility>
#include <vector>

struct model
{
    std::string prozessor_;
    int ram_;
    int bildschirm_;
};

struct constraint
{
    std::string prozessor_;
    int ram_;
    int bildschirm_;
};

struct option
{
    std::vector<std::string> prozessor_;
    std::vector<std::string> ram_;
    std::vector<std::string> bildschirm_;
};

class Checker {
    option option_;
    std::vector<constraint> constraints_;
    std::vector<model> models_;
public:
    void readData(const std::string &options,
                  const std::string &constraints,
                  const std::string &models);
private:
    void setOption(std::vector<std::string> param);
};
#endif // CHECKER_H_