#include "VendingMachine.h"
#include <iostream>

using namespace std;
using namespace VendingMachines;

float VendingMachine::GetInsertedAmount() 
{
    return 0;
}

string VendingMachine::GetDisplay()
{
    string message = "";

    if (GetInsertedAmount() == 0) {
        message = "INSERT COIN";
    }

    return message;
}
