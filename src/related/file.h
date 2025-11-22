#ifndef FILE_H
#define FILE_H
#include "iostream"



extern std::string getExecutablePath();
extern std::string getExecutableDir();
extern std::string pathJoin(const std::string& base, const std::string& rel);
#endif
