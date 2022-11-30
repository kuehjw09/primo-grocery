#include "../include/Inventory.h"
#include "../include/project_helper.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

Inventory::Inventory() {}

void Inventory::readInventoryFromFile()
{
  // read items from file and populate categories
  ifstream itemsFS;
  itemsFS.open("../resources/items.txt");
  if (!itemsFS.is_open())
  {
    cout << "Failed to open file" << endl;
    return;
  }

  string input;
  getline(itemsFS, input);
  while (!itemsFS.fail())
  {

    Item *item = new Item(parseLine(input, '\t'));

    // populating category list member
    categories[item->getCategoryId() - 1].addItem(item);

    getline(itemsFS, input); // next line
  }
  itemsFS.close();
}

bool Inventory::writeInventoryToFile(std::string path)
{
  std::ofstream itemsOut;
  itemsOut.open(path, std::ios::out);
  if (!itemsOut.is_open())
  {
    std::cout << "Unable to write to items file! [" << path << "]" << std::endl;
    return false;
  }

  for (Category cat : categories)
    itemsOut << cat.asFileString();

  return true;
}