#include <iostream>
#include <iomanip>

using namespace std;

int main() {
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
 
 return 0;
}