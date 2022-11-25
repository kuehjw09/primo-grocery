#include "../include/Error.h"

#include <iostream>

using namespace std;

void errClass::display() {
 cout << "\n\tError: " << errorMessage << " Error Code: " << errorCode << endl;
}