#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <sstream>

class Item {
    private:
        std::string name;
        std::string id;
        double price;
        int qty;

    public:
        Item() {};
        ~Item() {}
        Item(std::string name, std::string id, double price = -1, int qty = -1): name(name), id(id), price(price), qty(qty) { }
        Item(std::vector<std::string> props): Item(props.at(1), props.at(0), stod(props.at(2)), stoi(props.at(3))) {}

        std::string asFileLine();

        std::string getName() const { return name; }
        std::string getId() const { return id; }
        int getCategoryId() const { return id[0] - 64;} // ASCII 
        double getPrice() const { return price; }
        int getQty() const { return qty; }

        void decQty(int amount) { this->qty -= amount; }
        void print(int index = -1);
};

#endif
