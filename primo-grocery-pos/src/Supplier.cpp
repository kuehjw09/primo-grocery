#include "../include/Supplier.h"
#include "../include/SupplyOrder.h"
#include "../include/project_helper.h"
#include <iostream>
#include <fstream>

std::string Supplier::asFileString() const
{
    std::stringstream ss;
    ss << this->getID() << "\t";
    ss << this->getName() << "\t";
    ss << this->getAddress() << "\t";
    ss << this->getPhone() << "\t";
    ss << this->getEmail() << "\t";
    ss << "\n";
    return ss.str();
}

void Supplier::print() const
{
    cout << std::left << setw(8) << this->getID() << " ";
    cout << setw(32) << std::left << ("\'" + this->getName() + "\'") << " ";
    cout << setw(48) << std::left << this->getAddress() << "\n\t\t";
    cout << setw(16) << std::left << this->getPhone() << " ";
    cout << setw(16) << std::left << this->getEmail() << endl;
    cout << endl;
}

bool Supplier::overwriteSuppliers(vector<Supplier> suppliers, string path)
{
    std::ofstream suppliersOut;
    suppliersOut.open(path, std::ios::out);
    if (!suppliersOut.is_open())
    {
        std::cout << "Unable to write to suppliers file! [" << path << "]" << std::endl;
        return false;
    }

    for (Supplier sup : suppliers)
        suppliersOut << sup.asFileString();

    suppliersOut.close();
    return true;
}

vector<Supplier> Supplier::readSuppliers(string path)
{
    vector<Supplier> suppliers;
    ifstream supplierFS;
    supplierFS.open(path);
    if (!supplierFS.is_open())
        return suppliers;

    string input;
    getline(supplierFS, input);
    while (!supplierFS.fail())
    {
        vector<string> tokens = parseLine(input, '\t');
        Supplier supplier(tokens);
        suppliers.push_back(supplier);
        getline(supplierFS, input);
    }
    return suppliers;
}

Supplier Supplier::readSupplier(string supplier_id, string path)
{
    std::ifstream supplierFS;
    supplierFS.open(path);
    if (supplierFS.is_open())
    {
        string input;
        getline(supplierFS, input);
        while (!supplierFS.fail())
        {
            vector<string> tokens = parseLine(input, '\t');
            if (tokens[0] == supplier_id)
                return Supplier(tokens);
            getline(supplierFS, input);
        }
    }
    return readSupplier("0000", path);
}