#ifndef INVENTORY_H
#define INVENTORY_H

#include "Category.h"

class Inventory
{
public:
  Inventory();
  void readInventoryFromFile();
  bool writeInventoryToFile(std::string path);
  Category categories[12] = {
      Category(1, "Beverages"),
      Category(2, "Bread & Bakery"),
      Category(3, "Breakfast & Cereal"),
      Category(4, "Cookies, Snacks & Candy"),
      Category(5, "Dairy, Eggs & Cheese"),
      Category(6, "Produce"),
      Category(7, "Grains, Pasta & Sides"),
      Category(8, "Meat & Seafood"),
      Category(9, "Miscellaneous"),
      Category(10, "Paper Products"),
      Category(11, "Pet Care"),
      Category(12, "Pharmacy")};
  ;
};

#endif