#include "../include/AdminTransaction.h"

#include <iostream>
#include "../include/project_helper.h"

using namespace std;

void AdminTransaction::displayMenu()
{
    char choice;

    do
    {
        clearConsole();
        cout << "\n\t\t\tPRIMO GROCERY\n";
        cout << "\n\tADMIN TRANSACTION\n";
        cout << "\t" << getDateString();
        cout << "\n\n\t************   Select an action   ***********\n";
        cout << "\n\t**             1.View Sales By Date       **" << endl;
        cout << "\t**             2.View Balance Sheet        **" << endl;
        cout << "\t**             3.Order Supplies            **" << endl;
        cout << "\t**             4.EXIT                      **" << endl;
        cout << "\n\t*********************************************\n";
        cout << "\n\tEnter your choice-----> ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            // display sales by date
            break;
        case '2':
            // display balance sheet
            break;
        case '3':
            // display list of items needing restock
            break;
        case '4':
            // confirm action
            clearConsole();
            cout << "\n\n\n\tAre you sure you want to cancel?\n\tPress 1 to confirm. Any Key. CANCEL----> ";
            cin >> choice;
            if (choice == '1')
                choice = '0';
            else
                choice = '1';
            break;
        default:
            cout << "\n\tInvalid choice";
            choice = '1';
            break;
        }
    } while (choice != '0' && choice == '1');
}
