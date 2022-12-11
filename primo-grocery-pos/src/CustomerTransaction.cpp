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

void categoryMenu(Category &c);
void displayCategories();
Customer getCustomerInformation();

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

void CustomerTransaction::displayMenu()
{
  clearConsole();
  cout << "\n\t\t\tPRIMO GROCERY\n";
  cout << "\n\tCUSTOMER TRANSACTION\n";
  cout << "\t" << getDateString();
  cout << "\n\t---\n";
  Sale *sale = new Sale(getCustomerInformation());
  currentSale = *sale;

  int choice;

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
    choice = fetchIntegerChoice();

    switch (choice)
    {
    case 1:
      clearConsole();
      displayAddItemsMenu();
      break;
    case 2:
      // view cart
      if (!(currentSale.getCartSize() == 0))
      {
        clearConsole();
        currentSale.displayItems();
      }
      else
        cout << "\n\tCannot view empty cart.";
      choice = 1;
      break;
    case 3:
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
          incrementSaleId(currentSale.getId());                      // update id.txt
          inventory->writeInventoryToFile("../resources/items.txt"); // update inventory

          try
          {
            currentSale.writeSaleToFile(); // store sale info
          }
          catch (errClass error)
          {
            error.display();
          }
          currentSale.generateSalesReceipt();
          choice = 0;
          break;
        }
      }
      else
        cout << "\n\tCannot checkout with an empty cart.";
      choice = 1;
      break;
    case 4:
      // confirm action
      clearConsole();
      cout << "\n\n\n\tAre you sure you want to cancel?\n\tPress 1 to confirm. Any Key. CANCEL----> ";
      cin >> choice;
      if (choice == 1)
        choice = 0;
      else
        choice = 1;
      break;
    default:
      cout << "\n\tInvalid choice";
      choice = 1;
      break;
    }

  } while (choice != 0 && choice == 1);
  clearConsole();
  return;
}

/**
 * Allow customer to select a department to browse for items.
 */
void CustomerTransaction::displayAddItemsMenu()
{
  printHeader();
  int selection;

  // display categories
  cout << "\n\t*****************  Select a category    **********\n\n";

  for (Category cat : inventory->categories)
  {
    cout << "\t**\t" << cat.getId() << ". " << cat.getName() << setw(30 - cat.getName().length()) << right << "\t\t**" << endl;
  }

  cout << "\n\t**************************************************\n";
  cout << "\n\tEnter selection (0 to exit) ----> ";
  selection = fetchIntegerChoice();


  if (selection < 1 || selection > inventory->getNumCategories())
  {
    return;
  }

  try
  {
    categoryMenu(inventory->categories[selection - 1]);
  }
  catch (errClass error)
  {
    clearConsole();
    error.display();
    displayAddItemsMenu();
  }
}

/**
 * For a valid department, display its items and get input from the user to select the item and quantity of the
 * item they would like to add to the Sale. Create a SaleItem with this information and call a method in the Sale
 * class to add the SaleItem to the Sale.
 */
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
  selection = fetchIntegerChoice();

  if (selection > c.numItems() || selection < 1)
  {
    errClass error("Invalid selection", 1);
    throw error;
  }

  selection -= 1;

  Item *i = c.getItemAtMenuIndex(selection);

  cout << "\n";
  c.print_header();
  i->print();

  if (i->getUnits() == "")
    cout << "\n\n\tEnter a quantity ----> ";
  else
  {
    cout << "\n\n\tEnter quantity (" << i->getUnits() << ") ----> ";
  }
  quantity = fetchIntegerChoice();

  if (quantity > i->getQuantity() || quantity < 0)
  {
    errClass error("Invalid quantity.", 3);
    throw error;
  }

  // add item to cart
  try
  {
    currentSale.addSaleItem(i, quantity);
  }
  catch (errClass error)
  {
    throw error;
  }
}

/**
 * Collect a user's information and return a Customer object to create an instance of Sale.
 */
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