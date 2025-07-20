#include <string>

namespace VendingMachines {

    class Coin {
    };

    class VendingMachine {
    public:
        float GetInsertedAmount();
        std::string GetDisplay();
    };

}