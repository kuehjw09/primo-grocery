#include "../include/CustomerTransaction.h"
#include "../include/Sale.h"
#include "../include/Inventory.h"
#include "../include/SaleItem.h"
#include "../include/Error.h"
#include "../include/project_helper.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

static Sale currentSale;
static Inventory inventory;

void printHeader();
void categoryMenu(Category &c);
void displayCategories();
Customer getCustomerInformation();

void CustomerTransaction::displayMenu()
{
  clearConsole();

  inventory.readInventoryFromFile();

  Sale *sale = new Sale(getCustomerInformation());
  currentSale = *sale;

  delete sale;

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

    switch (choice)
    {
    case '1':

      clearConsole();

      displayCategories();

      break;
    case '2':
      // view cart
      if (!(currentSale.getCartSize() == 0))
      {
        currentSale.displayItems();
      }
      else
        cout << "\n\tCannot view empty cart.";
      choice = '1';
      break;
    case '3':
      // get customer payment
      if (!(currentSale.getCartSize() == 0))
      {
        clearConsole();
        printHeader();
        if (currentSale.checkout()) // successful purchase
        {
          /**
           * the following sequence of method calls finalizes a sales transaction
           */
          incrementSaleId(currentSale.getId());                     // update id.txt
          inventory.writeInventoryToFile("../resources/items.txt"); // update inventory

          try
          {
            currentSale.writeSaleToFile(); // store sale info
          }
          catch (errClass error)
          {
            error.display();
          }
          currentSale.generateSalesReceipt();
          choice = '0';
          break;
        }
      }
      else
        cout << "\n\tCannot checkout with an empty cart.";
      choice = '1';
      break;
    case '4':
      // confirm action
      clearConsole();
      cout << "\n\n\n\tAre you sure you want to cancel?\n\tPress 1 to confirm. Any Key. CANCEL----> ";
      cin >> choice;
      if (choice == '1')
        choice = '0';
      else
        choice = '1';
      break;
    default:
      cout << "\n\tInvalid choice";
      choice = '1';
      break;
    }

  } while (choice != '0' && choice == '1');

  currentSale.removeItems();

  clearConsole();

  for (Category cat : inventory.categories)
  {
    cat.deleteItems();
  }

  return;
}

void categoryMenu(Category &c)
{
  if (c.numItems() == 0)
  {
    errClass error("No items in selection.", 2);
    throw error;
  }

  clearConsole();
  cout << "\n\t\tDepartment: " << c.getName() << endl;

  c.displayItems();

  int selection;
  int quantity;

  cout << "\n\n\tEnter a selection ----> ";
  cin >> selection;

  if (selection > c.numItems())
  {
    errClass error("Invalid selection", 1);
    throw error;
  }

  selection -= 1;

  // Test code for fetching item, decreasing quantity & saving to new temporary file
  Item *i = c.getItemAtMenuIndex(selection);

  cout << "\n";
  c.print_header();
  i->print();
  // i->decQty(1);
  // i->print();

  cout << "\n\n\tEnter a quantity ----> ";
  cin >> quantity;

  if (quantity > i->getQty())
  {
    errClass error("Exceed avail. quantity.", 3);
    throw error;
  }

  // add item to "cart"
  try
  {
    currentSale.addSaleItem(i, quantity);
  }
  catch (errClass error)
  {
    throw error;
  }
}

void displayCategories()
{
  int selection;
  printHeader();
  // display categories
  cout << "\n\t*****************  Select a category    **********\n\n";

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
  try
  {
    categoryMenu(inventory.categories[selection - 1]);
  }
  catch (errClass error)
  {
    clearConsole();
    error.display();
    displayCategories();
  }
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
  stringstream ss;
  ss << fixed << setprecision(2) << "$" << currentSale.getTotalPrice();
  cout << "\n\n\tCustomer: " << currentSale.getCustomer().getName() << endl;
  cout << "\tCart: (" << currentSale.getCartSize() << ")\n";
  cout << "\tSubtotal: " << ss.str() << endl;
}
