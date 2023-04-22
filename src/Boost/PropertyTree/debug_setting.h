
#ifndef CPP_PRACTICE_DEBUGSETTING_H
#define CPP_PRACTICE_DEBUGSETTING_H

#include <string>
#include <set>

struct DebugSetting {
    std::string file_;
    int level_;
    std::set<std::string> modules_;
    void load(const std::string &filename);
    void save(const std::string &filename);
};


#endif //CPP_PRACTICE_DEBUGSETTING_H
