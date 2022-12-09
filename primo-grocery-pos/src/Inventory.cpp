#include "../include/Inventory.h"
#include "../include/Error.h"
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
  ifstream itemsFS;

  // read in category names
  itemsFS.open("../resources/categories.txt");
  if (!itemsFS.is_open())
  {
    cout << "Failed to open file [categories.txt]" << endl;
    return;
  }

  int i = 0;
  string input;
  getline(itemsFS, input);
  while (!itemsFS.fail())
  {
    Category *cat = new Category(parseLine(input, '\t'));
    categories[i] = (*(cat));
    i++;
    getline(itemsFS, input);
  }

  itemsFS.close();

  // read in individual items
  itemsFS.open("../resources/items.txt");
  if (!itemsFS.is_open())
  {
    cout << "Failed to open file" << endl;
    return;
  }

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

  itemsOut.close();
  return true;
}

vector<Item *> Inventory::getBelowThresholdQty()
{
  vector<Item *> itemsBelowThresholdQty;
  for (Category cat : categories)
  {
    for (Item *i : cat.getItems())
      if (i->isBelowThreshold())
        itemsBelowThresholdQty.push_back(i);
  }

  return itemsBelowThresholdQty;
}

/**
 * Returns a vector of SaleByDateItem objects having saleID equal to the
 * ID passed to this method.
 */
vector<SaleItem *> Inventory::readSalesById(string saleId)
{
  vector<SaleItem *> items; // to store items matching saleId
  ifstream inFS;

  inFS.open(itemsOutFilePath);

  if (!inFS.is_open())
  {
    cout << "failed to open [" << itemsOutFilePath << "]" << endl;
    assert(false);
  }

  string input;
  getline(inFS, input);

  vector<string> tokens;
  string id;
  while (!inFS.fail())
  {
    tokens = parseLine(input, '\t');
    if (tokens.at(0) == saleId) // select from items-out where id == saleId
    {
      SaleItem *si;
      si->getItem()->getId() = tokens.at(1);
      si->setQuantityForAdmin(stoi(tokens.at(2)));

      items.push_back(si);
    }

    getline(inFS, input);
  }
  inFS.close();
  return items;
}