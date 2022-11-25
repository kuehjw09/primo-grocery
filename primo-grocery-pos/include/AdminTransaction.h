#pragma once
#include "Transaction.h"

class AdminTransaction : public Transaction {
 public:
  AdminTransaction() {}
  void displayMenu();
};