#ifndef SALE_ITEM_H
#define SALE_ITEM_H

#include "Item.h"

class SaleItem {
 Item item; 
 int qty;
 double totalPrice;
 public:
  SaleItem() {}
  ~SaleItem() {}
  SaleItem(const SaleItem& si) :SaleItem(si.item, si.qty, si.totalPrice) {}
  SaleItem(Item item, int qty, double totalPrice) : item(item), qty(qty), totalPrice(totalPrice) {}
  Item getItem() {return item;}
  int getQty() {return qty;}
  double getTotalPrice() {return totalPrice;}
};

#endif