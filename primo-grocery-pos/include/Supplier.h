#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>
#include <vector>

using std::string, std::vector;

static const std::string suppliersFilePath = "../resources/suppliers.txt";

class Supplier {
    public:
        Supplier(string id, string name, string address, string phone_num, string email);
        Supplier(vector<string> tokens): id(tokens[0]), name(tokens[1]), address(tokens[2]), phone_num(tokens[3]), email(tokens[4]) {};

        static Supplier readSupplier(string supplier_id, string path = suppliersFilePath);

        string getID() const { return id; }
        string getName() const { return name; }
        string getAddress() const { return address; }
        string getPhone() const { return phone_num; }
        string getEmail() const { return email; }

    private:
        string id;
        string name;
        string address;
        string phone_num;
        string email;
};

#endif