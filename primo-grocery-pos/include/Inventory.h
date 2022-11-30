#ifndef INVENTORY_H
#define INVENTORY_H

#include "Category.h"

class Inventory
{
public:
  Inventory();
  Category categories[12];
  void readInventoryFromFile();
  bool writeInventoryToFile(std::string path);
};

#endif