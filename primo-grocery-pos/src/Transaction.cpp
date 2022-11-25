#include "../include/Transaction.h"
#include "../include/AdminTransaction.h"
#include "../include/CustomerTransaction.h"
#include "../include/SupplierTransaction.h"
#include "../include/Error.h"


Transaction* TransactionFactory::createTransaction(string transactionDetails) {
 if (transactionDetails == "Admin")
  return new AdminTransaction;
 else if (transactionDetails == "Customer")
  return new CustomerTransaction;
 else if (transactionDetails == "Supplier")
  return new SupplierTransaction;
 else {
  errClass err("Invalid Transaction", 1);
  throw err;
 }
}