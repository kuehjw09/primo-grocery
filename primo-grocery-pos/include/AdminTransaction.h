#pragma once
#include "Transaction.h"
#include "project_helper.h"
#include "SupplyOrder.h"

class AdminTransaction : public Transaction
{
public:
  AdminTransaction(Inventory *inventory) : Transaction(inventory) {}
  void displayMenu();
  void displaySalesByDateMenu();
  void displayBalanceSheet();
  void displayRestockingMenu(int mode = 0);

  double totalDebtOn(std::string date);
  vector<SupplyOrder> supplyOrdersOn(std::string date, std::string path = ordersFilePath);
};