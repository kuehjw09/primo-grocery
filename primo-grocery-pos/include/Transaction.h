#pragma once

#include <string>

using namespace std;

// Abstract Transaction class
class Transaction {
 public:
 Transaction() {}
 virtual void displayMenu() = 0;
};

class TransactionFactory {
 public:
 TransactionFactory() {}
 static Transaction* createTransaction(string);
};