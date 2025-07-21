#pragma once

namespace VendingMachines {

    enum class CoinSize {
        Penny, Nickel, Dime, Quarter
    };

    enum class CoinWeight {
        Penny, Nickel, Dime, Quarter
    };

    enum class CoinValue {
        Invalid = 0,
        Penny = 1,
        Nickel = 5,
        Dime = 10,
        Quarter = 25
    };

    class Coin {
    public:
        Coin(CoinSize, CoinWeight);
        CoinWeight Weight;
        CoinSize Size;
        CoinValue Value;
    };

}