#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <cstdlib>
#include <iomanip>

class Item {
    private:
        std::string name;
        double price;
        int qty;

    public:
        Item();
        Item(std::string name, double price = -1, int qty = -1): name(name), price(price), qty(qty) { }

        std::string getName() { return name; }
        double getPrice() { return price; }
        int getQty() { return qty; }

        void print(int index = -1) {
            std::string fmtname = (index == -1) ? "" : std::to_string(index+1) + ": ";
            std::cout << std::setw(15) << (fmtname + this->getName()) << " ";
            std::cout << std::setw(8) << std::left << this->getPrice() << " ";
            std::cout << std::setw(8) << this->getQty() << std::endl;
        }

        static void print_header() {
            std::cout << "---------------------------------" << std::endl;
            std::cout << std::left << std::setw(15) << "Item Name" << " ";
            std::cout << std::setw(8) << std::left << "Price" << " ";
            std::cout << std::setw(8) << std::left << "Quantity" << std::endl;
            std::cout << "---------------------------------" << std::endl;
        }
};

#endif
