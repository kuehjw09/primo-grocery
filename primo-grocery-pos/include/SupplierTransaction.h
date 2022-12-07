#pragma once
#include "Transaction.h"

class SupplierTransaction : public Transaction {
 public:
  SupplierTransaction(Inventory* inventory): Transaction(inventory) {}
  void displayMenu();

  void displayHistoryMenu();
  void displaySuppliers();
  void displayNewSupplier();
};