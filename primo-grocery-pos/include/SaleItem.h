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
  SaleItem(const SaleItem& si) :SaleItem(si.item, si.qty) {}
  SaleItem(Item item, int qty) : item(item), qty(qty), totalPrice(item.getPrice() * qty) {}
  Item getItem() {return item;}
  int getQty() {return qty;}
  double getTotalPrice() {return totalPrice;}
  void print(int index = -1);
};

#endif