#pragma once
#include "Transaction.h"

class CustomerTransaction : public Transaction {
 public:
  CustomerTransaction() {}
  void displayMenu();
};