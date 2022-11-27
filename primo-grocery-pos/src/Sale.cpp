#include "../include/Sale.h"

void Sale::displayItems() {
 char choice;
 do {
  print_header();


    int count = 0;
    std::list<SaleItem>::iterator i;
    for (i = saleItems.begin(); i != saleItems.end(); i++) {
        i->print(count);
        count++;
    }

    cout << "\n\n\t******** What would you like to do? ********\n";
    cout << "\n\t**          1.Remove Item                 **\n";
    cout << "\t**          2.Clear Cart                  **\n";
    cout << "\n\n\tInput a selection. (0 to EXIT) ----> ";
    cin >> choice;

    switch (choice) {
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

void Sale::removeSaleItem(int index) {
 list<SaleItem>::iterator li = saleItems.begin();
 for (int i = 0; i < index; i++) {
  ++li;
 }
 saleItems.erase(li);
}

void Sale::removeItems() {
 saleItems.clear();
}

