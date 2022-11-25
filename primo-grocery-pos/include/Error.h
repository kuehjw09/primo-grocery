#pragma once

#include <string>
using namespace std;


// Error class
class errClass {
 string errorMessage;
 int errorCode;
 public:
  errClass() {}
  errClass(string errorMessage, int errorCode) :errorMessage(errorMessage), errorCode(errorCode) {}
  void display();
};