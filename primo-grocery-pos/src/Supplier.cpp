#include "../include/Supplier.h"
#include "../include/project_helper.h"
#include <iostream>
#include <fstream>


Supplier Supplier::readSupplier(string supplier_id, string path)
{
    std::ifstream supplierFS;
    supplierFS.open(path);
    if (supplierFS.is_open()) {
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