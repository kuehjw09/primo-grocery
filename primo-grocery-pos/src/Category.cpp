#include "../include/Category.h"

void Category::displayItems() {
    print_header();

    int count = 0;
    std::list<Item>::iterator i;
    
    for (i = items.begin(); i != items.end(); i++) {
        i->print(count);
        count++;
    }
}

Item Category::getItemAtMenuIndex(int index) {
    int count;

    Item found;
    for (Item i : items) {
        if (count == index) return i;
        count++;
    }
    return found;
}
