#include "../include/CustomerTransaction.h"
#include "../include/Category.h"
#include "../include/Sale.h"
#include "../include/SaleItem.h"
#include "../include/project_helper.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>


using namespace std;

void categoryMenu(Category& c);
bool writeCategories(std::string path);
void printHeader();

static Sale currentSale;
static Customer currentCustomer;

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

void categoryMenu(Category& c) {
  clearConsole();
  printHeader();

  c.displayItems();

  int selection;
  int quantity;

  cout << "\n\n\tEnter a selection ----> ";
  cin >> selection;
  selection -= 1;

  // Test code for fetching item, decreasing quantity & saving to new temporary file
  Item* i = c.getItemAtMenuIndex(selection);

  i->print();
  // i->decQty(1);
  // i->print();

  cout << "\n\n\tEnter a quantity ----> ";
  cin >> quantity;

  // create sale item and add to "cart"
  SaleItem currentItem(*(i), quantity);
  currentSale.addSaleItem(currentItem);

  // write to file after purchase 
  // writeCategories("../resources/items_write_test.txt");
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

void getCurrentInventory() {
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

    // populating category list member
    categories[item->getCategoryId() - 1].addItem(item);

    getline(itemsFS, input); // next line
  }
}

void displayCategories() {
   int selection;
  clearConsole();
  printHeader();
   // display categories
   cout << "\n\n\t*****************  Select a category    **********\n\n";

 for (Category cat : categories) {
  cout << "\t**\t" << cat.getId() << ". " << cat.getName() << setw(30 - cat.getName().length()) << right << "\t\t**" << endl;
 }

cout << "\n\t**************************************************\n";
 cout << "\n\tEnter selection (0 to exit) ----> ";
  cin >> selection;

  if (selection == 0) {
    return;
  }

  // display items in selected category
  categoryMenu(categories[selection -1]);
}

Customer getCustomerInformation() {
  string first;
  string last;
  string phoneNumber;
  cout << "\n\tEnter First Name:\n\t-----> "; 
  cin >> first;
  cout << "\n\tEnter Last Name:\n\t-----> "; 
  cin >> last;
  cout << "\n\tEnter Phone Number:\n\t-----> ";
  cin >> phoneNumber;

  clearConsole();
  return Customer(first, last, phoneNumber);
}

void printHeader() {
    cout << "\n\t\t\tPRIMO GROCERY\n";
    cout << "\n\tCUSTOMER TRANSACTION\n";
		cout << "\t" << getDateString();
    
    cout << "\n\n\tCustomer: " << currentCustomer.getName() << 
      "\n\tCart: " << currentSale.getCartSize() << "\n\n";
}

void CustomerTransaction::displayMenu() {
  clearConsole();

  // read in items from file
  getCurrentInventory();
  
  currentCustomer = getCustomerInformation();

char choice; 

do {
    clearConsole();
    printHeader();
		cout << "\n\n\t************   Select an action   ***********\n";
		cout << "\n\t**             1.Add Items                 **" << endl;
		cout << "\t**             2.View Cart                 **" << endl;
		cout << "\t**             3.Checkout                  **" << endl;
		cout << "\t**             4.CANCEL                    **" << endl;
		cout << "\n\t*********************************************\n";
		cout << "\n\tEnter your choice-----> ";
    cin >> choice;
    cout << "\n\n";


  switch (choice) {
    case '1':

      displayCategories();
    break;
    case '2':
      // view cart
      currentSale.displayItems();
    break;
    case '3':
      // get customer payment
    break;
    case '4':
      // confirm action 
      clearConsole();
      cout << "\n\n\n\tAre you sure you want to cancel?\n\tPress 0 to confirm. Any Key. CANCEL----> ";
      cin >> choice;
  
    break;
    default:
    cout << "\n\tInvalid choice";
    break;
  }


  
} while (choice != '0');

  currentSale.removeItems();
    
  clearConsole();
      
   for (Category cat : categories) {
    cat.deleteItems();
  }

  return;

}
