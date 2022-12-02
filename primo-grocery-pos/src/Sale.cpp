#include <cassert>
#include "../include/Sale.h"

// default constructor
Sale::Sale()
{
  id = generateSaleId(); // get unique sale id
  totalPrice = 0.0;
}

// parametric constructor
Sale::Sale(const Customer &customer) : customer(customer)
{
  id = generateSaleId(); // get unique sale id
  totalPrice = 0.0;
}

void Sale::displayItems()
{
  char choice;
  do
  {
    cout << "\n\t\tVIEW CART\n";
    print_header();

    int count = 0;
    std::list<SaleItem>::iterator i;
    for (i = saleItems.begin(); i != saleItems.end(); i++)
    {
      i->print(count);
      count++;
    }

    cout << "\n\n\t******** What would you like to do? ********\n";
    cout << "\n\t**          1.Remove Item                 **\n";
    cout << "\t**          2.Clear Cart                  **\n";
    cout << "\n\t********************************************\n";
    cout << "\n\n\tInput a selection. (0 to EXIT) ----> ";
    cin >> choice;

    switch (choice)
    {
    case '1':
      int index;
      cout << "\n\n\t Enter the item to be removed----> ";
      cin >> index;
      removeSaleItem(index - 1);
      break;
    case '2':
      removeItems();
      return;
      break;
    default:
      cout << "\n\n\tInvalid Selection.\n";
      break;
    }
  } while (choice != '0');
}

void Sale::removeSaleItem(int index)
{
  list<SaleItem>::iterator li = saleItems.begin();
  for (int i = 0; i < index; i++)
  {
    ++li;
  }
  saleItems.erase(li);

  setTotalPrice(calculateTotalPrice());
}

void Sale::removeItems()
{
  saleItems.clear();
  setTotalPrice(0.0);
}

double Sale::getTotalPrice()
{
  return totalPrice;
}

void Sale::setTotalPrice(double price)
{
  totalPrice = price;
}

double Sale::calculateTotalPrice()
{
  double total = 0.0;
  list<SaleItem>::iterator li = saleItems.begin();
  while (li != saleItems.end())
  {
    total += li->getTotalPrice();
    ++li;
  }

  return total;
}

std::string Sale::asFileLine()
{
  std::stringstream ss;
  ss << id << "\t";
  ss << getDateString() << "\t";
  ss << customer.asFileString();
  ss << totalPrice << "\t";
  ss << "\n";

  return ss.str();
}

void Sale::writeSaleToFile()
{
  // write to sales.txt
  ofstream outFS; // output file stream

  outFS.open("../resources/sales.txt", ios::out | ios::app); // open existing file and for appending output

  if (!outFS.is_open())
  {
    errClass error("Failed to open file", 4);
    throw error;
    assert(false);
  }

  outFS << this->asFileLine();

  outFS.close();

  // write SaleItems to items-out.txt
  outFS.open("../resources/items-out.txt", ios::out | ios::app);

  if (!outFS.is_open())
  {
    errClass error("Failed to open file", 4);
    throw error;
    assert(false);
  }

  std::list<SaleItem>::iterator li = saleItems.begin();
  while (li != saleItems.end())
  {
    outFS << li->asFileLine(); // output each sale item
    li++;
  }

  outFS.close();
}

bool Sale::checkout()
{
  char choice;
  double payment;
  double paid;
  std::list<SaleItem>::iterator i;

  stringstream ss;

  do
  {
    cout << "\n\t\tCHECKOUT";

    cout << "\n\n\t******** What would you like to do? ********\n";
    cout << "\n\t**          1.Make Payment                **\n";
    cout << "\t**          2.Add more items              **\n";
    cout << "\n\t********************************************\n";
    cout << "\n\n\tInput a selection. (0 to EXIT) ----> ";
    cin >> choice;

    switch (choice)
    {
    case '1':
      print_header();
      for (i = saleItems.begin(); i != saleItems.end(); i++)
      {
        i->print();
      }

      do
      {
        ss.str("");
        ss.clear();
        ss << fixed << setprecision(2) << "$" << getTotalPrice() - paid;
        cout << endl;
        cout << setw(88) << right << "---------------------------------\n";
        cout << setw(80) << right << "Amount due: " << ss.str() << endl;
        cout << setw(81) << right << "Enter payment amount -----> $";
        cin >> payment;

        paid += payment;
      } while (paid < getTotalPrice());

      if (paid > getTotalPrice())
      {
        cout << "\n\n";
        cout << setw(88) << right << "---------------------------------\n";
        cout << setw(81) << right << "Change Due -----> $" << paid - getTotalPrice() << endl;
      }
      // update item quantities
      updateItemQuantities(saleItems);

      cin.ignore();
      cout << "\n\n\tPress Enter to Continue";
      cin.ignore();

      return true;
      break;
    case '2':
      choice = '0';
      break;
    default:
      cout << "\n\n\tInvalid Selection.\n";
      if (!(choice == '0'))
        choice = '1';
      break;
    }
  } while (choice != '0' && choice == '1');

  return false;
}

void Sale::generateSalesReceipt()
{
  clearConsole();
  cout << "\n\n**Sales Receipt**\n\tPress Enter to Continue";
  cin.ignore();
}
