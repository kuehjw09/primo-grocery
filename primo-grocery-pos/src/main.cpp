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
    cin >> choice;
    cout << "\n\n";

    switch (choice)
    {
    case '1':
      try
      {
        Transaction *t = TransactionFactory::createTransaction("Admin");
        t->displayMenu();
      }
      catch (errClass err)
      {
        err.display();
      }
      break;
    case '2':
      try
      {
        Transaction *t = TransactionFactory::createTransaction("Customer");
        t->displayMenu();
      }
      catch (errClass err)
      {
        err.display();
      }
      break;
    case '3':
      try
      {
        Transaction *t = TransactionFactory::createTransaction("Supplier");
        t->displayMenu();
      }
      catch (errClass err)
      {
        err.display();
      }
      break;
    case '4':
      choice = '0';
      break;
    default:
      cout << "\n\tInvalid Choice";
      break;
    }

    if (choice != '0')
    {
      cin.clear();
      cin.sync();
      cout << "\n\t\t\tMAIN MENU\n";
      cout << "\n\n\n\tDo you want another Transaction?\n\tPress 1 to continue. 0. EXIT----> ";
      cin >> choice;
    }
    clearConsole();

  } while (choice != '0' && choice == '1');

  return 0;
}