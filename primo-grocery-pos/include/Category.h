#ifndef CATEGORY_H
#define CATEGORY_H

#include <list>
#include "Item.h"

class Category {
    public:
        Category(int id, std::string name): id(id), name(name) { }
        int getId() { return id; }
        std::string getName() { return name; }
        void addItem(Item item) {
            items.push_back(item);
        };
        void displayItems() {
            for (Item item : items) {
                item.print_header();
                item.print();
            }
        }
    private:
        int id;
        std::string name;
        std::list<Item> items;
};

#endif