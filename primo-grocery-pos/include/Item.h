#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <cstdlib>
#include <iomanip>

class Item {
    private:
        std::string name;
        std::string id;
        double price;
        int qty;

    public:
        Item();
        Item(std::string name, std::string id, double price = -1, int qty = -1): name(name), id(id), price(price), qty(qty) { }

        std::string getName() { return name; }
        std::string getId() { return id; }
        int getCategoryId() { return id[0] - 64;} // ASCII 
        double getPrice() { return price; }
        int getQty() { return qty; }

        void print(int index = -1) {
            std::string fmtname = (index == -1) ? "" : std::to_string(index+1) + ": ";
            std::cout << std::setw(15) << (fmtname + this->getName()) << " ";
            std::cout << std::setw(8) << std::left << this->getId() << " ";
            std::cout << std::setw(8) << this->getPrice() << " ";
            std::cout << std::setw(8) << this->getQty() << std::endl;
        }

        static void print_header() {
            std::cout << "---------------------------------" << std::endl;
            std::cout << std::left << std::setw(15) << "Item Name" << " ";
            std::cout << std::setw(8) << std::left << "ID" << " ";
            std::cout << std::setw(8) << std::left << "Price" << " ";
            std::cout << std::setw(8) << std::left << "Quantity" << std::endl;
            std::cout << "---------------------------------" << std::endl;
        }
};

#endif
