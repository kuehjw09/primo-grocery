#ifndef SUPPLYORDER_H
#define SUPPLYORDER_H
#include <string>
#include "../include/Item.h"

using std::string;

class SupplyOrder {
    public:
        SupplyOrder(string item_id, int quantity, string date, string supplier, string addr, string phone, string email): item_id(item_id), quantity(quantity), date_placed(date), supplier_name(supplier), contact_addr(addr), phone_num(phone), email_addr(email) {};
        SupplyOrder(std::vector<string> tokens): SupplyOrder(tokens[0], stoi(tokens[1]), tokens[2], tokens[3], tokens[4], tokens[5], tokens[6]) {};

        string asFileString() const;
        void processDelivery();
        void print();

        string getSupplier() const { return supplier_name; }
        string getDatePlaced() const { return date_placed; }
        string getAddress() const { return contact_addr; }
        string getPhone() const { return phone_num; }
        string getEmail() const { return email_addr; }

        string getOrderedID() const { return this->item_id; }
        int getQuantity() const { return this->quantity; }

    private:
        string item_id; 
        int quantity;

        bool processed;

        string date_placed; // TODO: Date class?
        string supplier_name;
        string contact_addr;
        string phone_num;
        string email_addr;
};

#endif