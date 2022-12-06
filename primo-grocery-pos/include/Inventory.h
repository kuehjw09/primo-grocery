#ifndef INVENTORY_H
#define INVENTORY_H

#include "Category.h"

static const std::string itemsFilePath = "../resources/items.txt";

class Inventory
{
public:

  Inventory();
  Category categories[12];
  void readInventoryFromFile();
  bool writeInventoryToFile(std::string path = itemsFilePath);
  std::vector<Item*> getBelowThresholdQty();
};

#endif