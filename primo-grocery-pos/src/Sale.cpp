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

void Sale::addSaleItem(Item *item, int qty)
{
  SaleItem i(item, qty, id);
  /**
   * This method traverses the entire list, it is not efficient. O(N)
   * Could implement a hash map to store items for faster retrieval.
   */
  // check for duplicate item
  list<SaleItem>::iterator li = saleItems.begin();
  while (li != saleItems.end())
  {
    if (li->getItem()->getId() == i.getItem()->getId())
    {
      try
      {
        li->setQty(li->getQty() + i.getQty());
        return;
      }
      catch (errClass error)
      {
        throw error;
      }
    }
    ++li;
  }

  setTotalPrice(totalPrice + i.getTotalPrice());
  saleItems.push_back(i);
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

int Sale::getItemCount()
{
  std::list<SaleItem>::iterator li = saleItems.begin();
  int count = 0;
  while (li != saleItems.end())
  {
    count += li->getQty();
    ++li;
  }

  return count;
}

void Sale::generateSalesReceipt()
{
  clearConsole();
  cout << "\n\n\t**Sales Receipt**\n";

  cout << "\n\n\tPRIMO GROCERY\n";
  cout << "\n\t"
       << "Date: " << getDateString() << setw(36 - getDateString().size()) << right << "Time: " << getTimeString() << endl;
  cout << "\t--------------------------------------------------\n";
  std::list<SaleItem>::iterator i;
  for (i = saleItems.begin(); i != saleItems.end(); i++)
  {
    stringstream ss;
    ss << "x" << i->getQty();
    Item *item = i->getItem();
    cout << "\n\t" << item->getId() << endl;
    cout << "\t" << item->getName() << setw(27 - item->getName().size()) << right << ss.str()
         << setw(23) << right << i->getTotalPrice() << endl;
  }
  cout << "\n\t--------------------------------------------------\n";
  cout << "\tSubtotal:                                 " << setw(8) << right << this->getTotalPrice() << endl;
  cout << "\tTax:                                      " << setw(8) << right << 0.00 << endl;
  cout << "\t--------------------------------------------------\n";
  stringstream ss;
  ss << "$" << fixed << setprecision(2) << this->getTotalPrice();
  cout << "\n\tTOTAL:" << setw(44) << right << ss.str() << endl;

  cout << "\n\n\n\tPrint:\t" << getDateString() << "\t" << getTimeString() << endl;

  cout << "\n\n\t                   Item Count: " << this->getItemCount() << endl;
  cout << "\tCustomer: " << customer.getName() << endl;
  cout << "\tSale " << getId() << endl;

  cout << "\n\n\n\tPress Enter to Continue";
  cin.ignore();
}
