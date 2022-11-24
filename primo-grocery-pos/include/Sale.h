#ifndef SALE_H
#define SALE_H

#include <list>
#include "SaleItem.h"
#include "Customer.h"

using namespace std;

class Sale {
 Customer customer;
 list<SaleItem> saleItems;
 double totalPrice;
 public:
  Sale() {}
  ~Sale() {}
  Sale(const Sale& s) {}

  void addSaleItem(SaleItem i) {saleItems.push_back(i);}

  void generateSalesReceipt() {}

};

#endif