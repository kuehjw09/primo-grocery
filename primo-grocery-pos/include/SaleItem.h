#ifndef SALE_ITEM_H
#define SALE_ITEM_H

#include "Item.h"
#include "Error.h"

class SaleItem
{
  Item *item;
  int qty; // count of Item in cart
  double totalPrice;
  unsigned saleId;

public:
  SaleItem() {}
  SaleItem(Item *item, int qty, unsigned id) : item(item), qty(qty), totalPrice(item->getPrice() * qty), saleId(id) {}
  SaleItem(const SaleItem &si);
  Item *getItem() { return item; }
  int getQty() { return qty; }
  double getTotalPrice() { return totalPrice; }
  void setItem(Item *i);
  void setQty(int q);
  void setQuantityForAdmin(int q);
  void setTotalPrice(double price) { totalPrice = price; }

  std::string asFileLine();

  void print(int index = -1);
};

#endif