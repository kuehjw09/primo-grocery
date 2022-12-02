#pragma once

#include <string>
#include "../include/Inventory.h"

using namespace std;

// Abstract Transaction class
class Transaction {
 public:
 Transaction(Inventory* inventory): inventory(inventory) {}
 virtual void displayMenu() = 0;
 Inventory* inventory;
};

class TransactionFactory {
 public:
 TransactionFactory() {}
 static Transaction* createTransaction(string, Inventory* inventory);
};