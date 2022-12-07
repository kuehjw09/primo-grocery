#ifndef SUPPLYORDER_H
#define SUPPLYORDER_H

#include <string>
#include "../include/Item.h"
#include "../include/Inventory.h"
#include "../include/Supplier.h"

using std::string;

class SupplyOrder {
    public:
        SupplyOrder(string item_id, int quantity, string date, Supplier supplier): item_id(item_id), quantity(quantity), date_placed(date), supplier(supplier), processed(false) {};
        SupplyOrder(string item_id, int quantity, string date, string supplier_id): SupplyOrder(item_id, quantity, date, Supplier::readSupplier(supplier_id)) {};
        SupplyOrder(std::vector<string> tokens): SupplyOrder(tokens[0], stoi(tokens[1]), tokens[2], tokens[3]) {};

        string asFileString() const;
        void processDelivery(Inventory* inventory);

        void print();

        Supplier getSupplier() const { return this->supplier; }
        string getDatePlaced() const { return this->date_placed; }
        string getOrderedID() const { return this->item_id; }
        int getQuantity() const { return this->quantity; }

        void setProcessed() { this->processed = true; }
        bool wasProcessed() const { return this->processed; }

    private:
        Supplier supplier;
        string item_id; 
        int quantity;

        bool processed;
        string date_placed; // TODO: Date class?
};

#endif