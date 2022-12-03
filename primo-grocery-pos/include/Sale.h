#ifndef SALE_H
#define SALE_H

#include <list>
#include <fstream>
#include "SaleItem.h"
#include "Customer.h"
#include "project_helper.h"

using namespace std;

class Sale
{
  unsigned id;
  Customer customer;
  list<SaleItem> saleItems;
  double totalPrice;

public:
  Sale();
  Sale(const Customer &customer);
  ~Sale() {}             // destructor
  Sale(const Sale &s) {} // copy constructor

  unsigned getId() { return id; }

  void addSaleItem(Item *item, int qty)
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
  void removeSaleItem(int index);
  void removeItems();
  void displayItems();

  int getCartSize() { return saleItems.size(); }
  double getTotalPrice();
  void setTotalPrice(double price);

  double calculateTotalPrice();

  Customer getCustomer() { return customer; }
  void setCustomer(Customer currentCustomer) { customer = currentCustomer; }

  static void print_header()
  {
    clearConsole();
    std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(27) << "Item Name"
              << " ";
    std::cout << std::setw(27) << std::left << "Category"
              << " ";
    std::cout << std::setw(10) << std::left << "Quantity"
              << " ";
    std::cout << std::setw(12) << std::left << "Unit Price"
              << " ";
    std::cout << std::setw(12) << std::left << "Total" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
  }

  std::string asFileLine(); // representation of the sale for writing to file

  bool checkout();             // finalize the sale
  void writeSaleToFile();      // write the sale to file
  void generateSalesReceipt(); // generate a sales receipt
};

#endif