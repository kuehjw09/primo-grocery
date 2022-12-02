#pragma once
#include "Transaction.h"
#include "Sale.h"

class CustomerTransaction : public Transaction
{
public:
  CustomerTransaction() {}
  void displayMenu();
};