#ifndef CATEGORY_H
#define CATEGORY_H

#include <list>
#include "Item.h"

class Category {
    public:
        Category(int id, std::string name): id(id), name(name) { }

        void displayItems();
        void addItem(Item item) {
            items.push_back(item);
        }

        static void print_header() {
            std::cout << "-------------------------------------------" << std::endl;
            std::cout << std::left << std::setw(15) << "Item Name" << " ";
            std::cout << std::setw(8) << std::left << "ID" << " ";
            std::cout << std::setw(8) << std::left << "Price" << " ";
            std::cout << std::setw(8) << std::left << "Quantity" << std::endl;
            std::cout << "-------------------------------------------" << std::endl;
        }

        int getId() { return id; }
        std::string getName() { return name; }

    private:
        int id;
        std::string name;
        std::list<Item> items;
};

#endif