#pragma once
#include "Transaction.h"
#include "Sale.h"

class CustomerTransaction : public Transaction
{
public:
  CustomerTransaction(Inventory *inventory) : Transaction(inventory) {}
  void displayMenu();
  void displayAddItemsMenu();
};