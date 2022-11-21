#include <iostream>
#include <iomanip>

using namespace std;

void salesWindow() {
 // display header
 // display categories
  string categories[] = {
  "Beverages",
  "Bread & Bakery",
  "Breakfast & Cereal",
  "Cookies, Snacks & Candy",
  "Dairy, Eggs & Cheese",
  "Produce",
  "Grains, Pasta & Sides",
  "Meat & Seafood",
  "Miscellaneous",
  "Paper Products",
  "Pet Care",
  "Pharmacy"
 };

 for (int i = 0; i < 12; i++) {
  cout << setw(2) << right << i + 1 << " - ";
  cout << setw(24) << left << categories[i];
  cout << endl;
 }

  // display input options

}

void managementWindow() {
 // display header
 // display input options

}


int main() {
  salesWindow();
 
 return 0;
}