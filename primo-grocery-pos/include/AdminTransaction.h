#pragma once
#include "Transaction.h"

class AdminTransaction : public Transaction {
 public:
  AdminTransaction(Inventory* inventory): Transaction(inventory) {}
  void displayMenu();
  void displayRestockingMenu(int mode = 0);
};