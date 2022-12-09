#include <iostream>
#include <fstream>

#include "../include/SupplierTransaction.h"
#include "../include/SupplyOrder.h"
#include "../include/Supplier.h"
#include "../include/Item.h"
#include "../include/project_helper.h"

using namespace std;
// using std::cout;
// using std::cin;
// using std::endl;
// using std::setw;

vector<SupplyOrder> readTransactions(string path = ordersFilePath);

void SupplierTransaction::displayMenu()
{
    int choice = -1;
    while (choice < 0 || choice > 3)
    {
        clearConsole();
        cout << "Supplier Transaction" << endl;
        cout << "Enter 0 to EXIT" << endl;
        cout << "Enter 1 to View order history" << endl;
        cout << "Enter 2 to View registered suppliers" << endl;
        cout << "Enter 3 to Register a new supplier" << endl;

        cout << endl
             << "Enter your choice ---> ";

        cin >> choice;
    }

    switch (choice)
    {
    case 0:
        clearConsole();
        return;
    case 1:
        displayHistoryMenu();
        break;
    case 2:
        displaySuppliers();
        break;
    case 3:
        displayNewSupplier();
        break;
    }

    clearConsole();
    displayMenu();
}

void appendSupplier(Supplier supplier)
{
}

void SupplierTransaction::displayNewSupplier()
{
    string id;
    string name;
    string address;
    string phone;
    string email;
    clearConsole();

    cin.ignore();
    cout << "The following menu will register a new supplier. Do you want to continue?" << endl;
    cout << "\t(y/n) ---> ";
    string cont;
    std::getline(cin, cont);
    if (cont == "y" || cont == "Y")
    {
        clearConsole();
        cout << "Input the name of the supplier ---> ";
        std::getline(cin, name);
        cout << endl
             << "Input the physical address of the supplier ---> ";
        std::getline(cin, address);
        cout << endl
             << "Input the phone number of the supplier ---> ";
        std::getline(cin, phone);
        cout << endl
             << "Input the email address of the supplier ---> ";
        std::getline(cin, email);
        cout << endl
             << "Input the ID desired for the supplier ---> ";
        std::getline(cin, id);

        vector<Supplier> suppliers = Supplier::readSuppliers();
        bool exists = false;
        for (Supplier s : suppliers)
        {
            if (s.getID() == id)
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            Supplier supplier(id, name, address, phone, email);
            suppliers.push_back(supplier);

            clearConsole();
            if (Supplier::overwriteSuppliers(suppliers))
                cout << "Supplier \'" << supplier.getName() << "\' successfully registered!" << endl;
        }
        else
        {
            clearConsole();
            cout << "A supplier with this ID already exists!" << endl;
        }
    }

    cout << endl
         << "Enter anything to return to the previous menu ---> ";

    string returnstr;
    cin >> returnstr;
}

void SupplierTransaction::displaySuppliers()
{
    clearConsole();
    vector<Supplier> suppliers = Supplier::readSuppliers();

    if (suppliers.size() > 1)
    {
        cout << "-------------------------------------------------------------------------------------------------" << std::endl;
        cout << std::left << setw(8) << "ID"
             << " ";
        cout << setw(32) << std::left << "Name"
             << " ";
        cout << setw(48) << std::left << "Address"
             << "\n\t\t";
        cout << setw(16) << std::left << "Phone"
             << " ";
        cout << setw(16) << std::left << "Email" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << std::endl;

        for (Supplier supplier : suppliers)
            if (supplier.getID() != "0000")
                supplier.print();

        cout << endl
             << "Input the supplier's ID to make changes, or 0 to EXIT ---> ";

        string choice;
        cin >> choice;

        if (choice == "0")
            return;
        else
        {
            Supplier s = Supplier::readSupplier(choice);
            if (s.getID() != "0000")
            {
                clearConsole();
                cout << "Selected supplier \'" << s.getName() << "\'" << endl;
                cout << "Input \'DELETE\' to permanently remove this supplier, " << endl
                     << "or input anything else to return to the previous menu." << endl;
                cout << endl
                     << "Enter your choice ---> ";
                string delsp;
                cin >> delsp;

                clearConsole();

                if (delsp == "DELETE")
                {
                    std::vector<Supplier>::iterator it = suppliers.begin();
                    while (it != suppliers.end())
                    {
                        if (s.getID() == it->getID())
                        {
                            suppliers.erase(it);
                            break;
                        }
                        it++;
                    }
                    if (Supplier::overwriteSuppliers(suppliers))
                    {
                        clearConsole();
                        cout << "Supplier removed!" << endl;
                    }
                }
            }
            else
            {
                cout << "Invalid Supplier ID!" << endl;
            }
        }
    }
    else
        cout << std::left << "There are currently no registered suppliers!" << endl
             << "Register a new supplier from the previous menu." << endl;

    cout << endl
         << "Enter anything to return to the previous menu ---> ";

    string returnstr;
    cin >> returnstr;
}

void SupplierTransaction::displayHistoryMenu()
{
    clearConsole();
    vector<SupplyOrder> orders = readTransactions(ordersFilePath);

    if (orders.size() != 0)
    {
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        cout << std::left << setw(8) << "Amount"
             << " ";
        cout << setw(12) << std::left << "Item ID"
             << " ";
        cout << setw(12) << std::left << "Date"
             << " ";
        cout << setw(32) << std::left << "Supplier"
             << " ";
        cout << setw(48) << std::left << "Address"
             << " ";
        cout << setw(16) << std::left << "Phone"
             << " ";
        cout << setw(16) << std::left << "Email" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

        for (SupplyOrder order : orders)
            order.print();
    }
    else
        cout << std::left << "There are currently no orders recorded!" << endl
             << "Create an order from the previous menu." << endl;

    cout << endl
         << "Enter anything to return to the previous menu ---> ";

    string returnstr;
    cin >> returnstr;
}

vector<SupplyOrder> readTransactions(string path)
{
    vector<SupplyOrder> orders;
    ifstream itemsFS;
    itemsFS.open(path);
    if (!itemsFS.is_open())
        return orders;

    string input;
    getline(itemsFS, input);
    while (!itemsFS.fail())
    {
        vector<string> tokens = parseLine(input, '\t');
        SupplyOrder order(tokens);
        orders.push_back(order);
        getline(itemsFS, input);
    }
    return orders;
}