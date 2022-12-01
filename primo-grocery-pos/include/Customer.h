#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>

using namespace std;

class Customer
{
  string firstName;
  string lastName;
  string phoneNumber;

public:
  Customer() {}
  ~Customer() {}
  Customer(string first, string last, string phone) : firstName(first), lastName(last), phoneNumber(phone) {}

  string getName() { return lastName + ", " + firstName; }
  string getPhoneNumber() { return phoneNumber; }

  string asFileString();
};

#endif