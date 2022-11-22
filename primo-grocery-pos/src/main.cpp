#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>


#include "../include/Category.h"
#include "../include/Item.h"

using namespace std;


Item parseItem(string &s, char delim) {
  stringstream ss;
  ss.str(s);
  vector<string> elems;
  // class Item member variables
  string name;
  string id;
  double price;
  int qty;

  string elem;
  while (getline(ss, elem, delim)) {
    elems.push_back(elem);
  }
   
  Item item(elems.at(1), elems.at(0), stod(elems.at(2)), stoi(elems.at(3)));
  return item;
} 


void salesWindow() {
 // display header

 // display categories
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
  Category(12, "Pharmacy")
 };

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
    
    Item item = parseItem(input, '\t');

    // item.print_header();
    // item.print();

    // populating category list member
    categories[item.getCategoryId() - 1].addItem(item);

    getline(itemsFS, input); // next line
  }
  

  // display items in selected category
  categories[selection - 1].displayItems();

  
}

void managementWindow() {
 // display header
 // display input options

}


int main() {
  salesWindow();
 
 return 0;
}