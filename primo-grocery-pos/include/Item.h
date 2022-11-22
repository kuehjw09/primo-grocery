#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>

class Item {
    private:
        std::string name;
        std::string id;
        double price;
        int qty;

    public:
        Item();
        Item(std::string name, std::string id, double price = -1, int qty = -1): name(name), id(id), price(price), qty(qty) { }
        Item(std::vector<std::string> props): Item(props.at(1), props.at(0), stod(props.at(2)), stoi(props.at(3))) {}
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
};

#endif
