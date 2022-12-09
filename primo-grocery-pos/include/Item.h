#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <sstream>

class Item
{
private:
    std::string name;
    std::string id;
    double price;
    int quantity;
    int restockQuantity;
    std::string units;

public:
    Item(){};
    ~Item() {}
    Item(std::string name, std::string id, int restockQty, double price = -1, int qty = -1)
        : name(name), id(id), restockQuantity(restockQty), price(price), quantity(qty) {}
    Item(std::vector<std::string> props);

    std::string getName() const { return name; }
    std::string getId() const { return id; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    int getRestockQuantity() const { return restockQuantity; } // restock threshold
    std::string getUnits() const { return units; }             // unit of measurement

    void setId(std::string id) { this->id = id; }
    void setQuantity(int quantity) { this->quantity = quantity; };
    void decQuantity(int amount = 1);

    bool isBelowThreshold() { return quantity < restockQuantity; }
    int getCategoryId() const { return id[0] - 64; } // ASCII
    std::string asFileLine();
    void print(int index = -1);
};

#endif
