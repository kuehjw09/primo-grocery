#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>
#include <vector>

using namespace std;

static const std::string suppliersFilePath = "../resources/suppliers.txt";

class Supplier
{
public:
    Supplier(string id, string name, string address, string phone_num, string email) : id(id), name(name), address(address), phone_num(phone_num), email(email){};
    Supplier(vector<string> tokens) : Supplier(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]){};

    static bool overwriteSuppliers(vector<Supplier> suppliers, string path = suppliersFilePath);
    static Supplier readSupplier(string supplier_id, string path = suppliersFilePath);
    static vector<Supplier> readSuppliers(string path = suppliersFilePath);

    void print() const;
    string asFileString() const;

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