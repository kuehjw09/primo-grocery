#include "../include/Transaction.h"
#include "../include/AdminTransaction.h"
#include "../include/CustomerTransaction.h"
#include "../include/SupplierTransaction.h"
#include "../include/Error.h"

Transaction *TransactionFactory::createTransaction(string transactionDetails, Inventory* inventory)
{
 if (transactionDetails == "Admin")
  return new AdminTransaction(inventory);
 else if (transactionDetails == "Customer")
  return new CustomerTransaction(inventory);
 else if (transactionDetails == "Supplier")
  return new SupplierTransaction(inventory);
 else
 {
  errClass err("Invalid Transaction", 1);
  throw err;
 }
}