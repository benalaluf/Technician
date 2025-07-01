#pragma once

#include <string>

class Exception {
  public:
    Exception(int status, std::string funcName);
    int status;
    std::string funcName;
};
