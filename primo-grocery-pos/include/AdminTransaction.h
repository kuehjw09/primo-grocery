#pragma once
#include "Transaction.h"

class AdminTransaction : public Transaction
{
public:
  AdminTransaction(Inventory *inventory) : Transaction(inventory) {}
  void displayMenu();
  void displaySalesByDateMenu();
  void displayRestockingMenu(int mode = 0);
};