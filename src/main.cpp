#include "VendingMachine.h"

using namespace VendingMachines;

int main()
{
    VendingMachine vendingMachine;
    printf("%s\n", vendingMachine.GetDisplay().c_str());
    return 0;
}
