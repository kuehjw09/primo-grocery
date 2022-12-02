#pragma once
#include "Transaction.h"

class SupplierTransaction : public Transaction {
 public:
  SupplierTransaction() {};
  void displayMenu();

  void displayHistoryMenu();
  void displayRestockingMenu(int mode = 0);
};