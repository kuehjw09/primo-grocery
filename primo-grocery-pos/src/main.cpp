#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

#include "../include/Category.h"
#include "../include/Item.h"
#include "../include/Error.h"
#include "../include/Transaction.h"
#include "../include/project_helper.h"

using namespace std;

int main()
{
  Inventory *inventory = new Inventory();
  inventory->readInventoryFromFile();

  char choice;

  do
  {
    cout << "\n\t\t\tPRIMO GROCERY\n";
    cout << "\n\t" << getDateString();
    cout << "\n\n\t************   Select the transaction ******\n";
    cout << "\n\t**             1.Admin                    **" << endl;
    cout << "\t**             2.Customer                 **" << endl;
    cout << "\t**             3.Supplier                 **" << endl;
    cout << "\t**             4.EXIT                     **" << endl;
    cout << "\n\t********************************************\n";
    cout << "\n\tEnter your choice-----> ";
    choice = fetchIntegerChoice();
    cout << "\n\n";

    string type = "";
    Transaction *t;
    switch (choice)
    {
    case 1:
      type = "Admin";
      break;
    case 2:
      type = "Customer";
      break;
    case 3:
      type = "Supplier";
      break;
    case 4:
      choice = 0;
      break;
    default:
      clearConsole();
      cout << "\n\tInvalid Choice";
      break;
    }

    if (type != "") {
      try
      {
        t = TransactionFactory::createTransaction(type, inventory);
        t->displayMenu();
      }
      catch (errClass err)
      {
        err.display();
      }
    }

    if (choice != 0)
    {
      cin.clear();
      cin.sync();
      cout << "\n\t\t\tMAIN MENU\n";
      cout << "\n\n\n\tDo you want another Transaction?\n\tPress 1 to continue. 0. EXIT----> ";
      choice = fetchIntegerChoice();
    }
    clearConsole();

  } while (choice != 0 && choice == 1);

  for (Category cat : inventory->categories)
  {
    cat.deleteItems();
  }

  delete inventory;

  return 0;
}