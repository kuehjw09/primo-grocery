#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

using namespace std;

class Customer {
  string name;
  string phoneNumber;
 public:
  Customer() {}
  ~Customer() {}
  Customer(string name, string phone): name(name), phoneNumber(phone) {}
  
};

#endif