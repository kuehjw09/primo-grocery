#ifndef INVENTORY_H
#define INVENTORY_H

#include "Category.h"
#include "SaleItem.h"

static const std::string itemsFilePath = "../resources/items.txt";
static const std::string itemsOutFilePath = "../resources/items-out.txt";

class Inventory
{
public:
  Inventory();
  Category categories[12];

  void readInventoryFromFile();
  bool writeInventoryToFile(std::string path = itemsFilePath);
  std::vector<Item *> getBelowThresholdQty();

  std::vector<SaleItem *> readSalesById(std::string saleId);
};

#endif