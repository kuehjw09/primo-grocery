#include "../include/CustomerTransaction.h"
#include "../include/Sale.h"
#include "../include/Inventory.h"
#include "../include/SaleItem.h"
#include "../include/project_helper.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

static Sale currentSale;
static Customer currentCustomer;
static Inventory inventory;

void printHeader();

void categoryMenu(Category &c)
{
  clearConsole();
  printHeader();

  c.displayItems();

  int selection;
  int quantity;

  cout << "\n\n\tEnter a selection ----> ";
  cin >> selection;
  selection -= 1;

  // Test code for fetching item, decreasing quantity & saving to new temporary file
  Item *i = c.getItemAtMenuIndex(selection);

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

void displayCategories()
{
  int selection;
  clearConsole();
  printHeader();
  // display categories
  cout << "\n\n\t*****************  Select a category    **********\n\n";

  for (Category cat : inventory.categories)
  {
    cout << "\t**\t" << cat.getId() << ". " << cat.getName() << setw(30 - cat.getName().length()) << right << "\t\t**" << endl;
  }

  cout << "\n\t**************************************************\n";
  cout << "\n\tEnter selection (0 to exit) ----> ";
  cin >> selection;

  if (selection == 0)
  {
    return;
  }

  // display items in selected category
  categoryMenu(inventory.categories[selection - 1]);
}

Customer getCustomerInformation()
{
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

void printHeader()
{
  cout << "\n\t\t\tPRIMO GROCERY\n";
  cout << "\n\tCUSTOMER TRANSACTION\n";
  cout << "\t" << getDateString();

  cout << "\n\n\tCustomer: " << currentCustomer.getName() << "\n\tCart: " << currentSale.getCartSize() << "\n\n";
}

void CustomerTransaction::displayMenu()
{
  clearConsole();

  inventory.readInventoryFromFile();

  currentCustomer = getCustomerInformation();

  char choice;

  do
  {
    clearConsole();
    printHeader();
    cout << "\n\n\t************   Select an action   ***********\n";
    cout << "\n\t**             1.Add Items                 **" << endl;
    cout << "\t**             2.View Cart                 **" << endl;
    cout << "\t**             3.Checkout                  **" << endl;
    cout << "\t**             4.EXIT                      **" << endl;
    cout << "\n\t*********************************************\n";
    cout << "\n\tEnter your choice-----> ";
    cin >> choice;
    cout << "\n\n";

    switch (choice)
    {
    case '1':
      printHeader();
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

  for (Category cat : inventory.categories)
  {
    cat.deleteItems();
  }

  return;
}
