#include "Coin.h"

using namespace VendingMachines;

Coin::Coin(CoinSize size, CoinWeight weight)
: Weight(weight)
, Size(size)
, Value(CoinValue::Invalid)
{

}

