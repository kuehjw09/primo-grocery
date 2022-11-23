#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>


#include "../include/Category.h"
#include "../include/Item.h"

using namespace std;

void categoryMenu(Category& c);
bool writeCategories(std::string path);

static Category categories[12] = {
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
    Category(12, "Pharmacy")
 };

vector<string> parseLine(string &s, char delim) {
  vector<string> elems;
  stringstream ss;
  ss.str(s);

  string elem;
  while (getline(ss, elem, delim)) {
    elems.push_back(elem);
  }
   
  return elems;
} 


void salesWindow() {
 // display header

 // display categories
 for (Category cat : categories) {
  cout << setw(2) << right << cat.getId() << " - ";
  cout << setw(24) << left << cat.getName();
  cout << endl;
 }

  // display input options
  cout << "Enter a number to view category (0 to exit): ";
  int selection;
  cin >> selection;

  if (selection == 0) {
    return;
  }

  // read items from file and populate categories
  ifstream itemsFS;
  itemsFS.open("../resources/items.txt");
  if (!itemsFS.is_open()) {
    cout << "Failed to open file" << endl;
    return;
  }

  string input;
  getline(itemsFS, input);
  while (!itemsFS.fail()) {
    
    Item* item = new Item(parseLine(input, '\t'));

    // item.print_header();
    // item.print();

    // populating category list member
    categories[item->getCategoryId() - 1].addItem(item);

    getline(itemsFS, input); // next line
  }
  

  // display items in selected category
  //categories[selection - 1].displayItems();
  categoryMenu(categories[selection -1]);
}

void categoryMenu(Category& c) {
  c.displayItems();

  int selection;
  cin >> selection;
  selection -= 1;

  // Test code for fetching item, decreasing quantity & saving to new temporary file
  Item* i = c.getItemAtMenuIndex(selection);

  i->print();
  i->decQty(1);
  i->print();

  writeCategories("../resources/items_write_test.txt");
}

bool writeCategories(std::string path) {
  std::ofstream itemsOut;
  itemsOut.open(path, std::ios::out);
  if (!itemsOut.is_open()) {
      std::cout << "Unable to write to items file! [" << path << "]" << std::endl;
      return false;
  }

  for (Category cat : categories) itemsOut << cat.asFileString();
  
  return true;
}

void managementWindow() {
 // display header
 // display input options

}


int main() {
  salesWindow();
 
  return 0;
}