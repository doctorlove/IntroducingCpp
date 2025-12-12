#include  <stdexcept>

#include "trade.h"

double stock_prices::Exchange::next_price() //<1>
{
    if (!asset) //<2>
    {
        throw std::invalid_argument{"No asset available"}; //<3>
    }
    prices.push_back(asset->get_price()); //<4>
    return const auto price = asset->next_price(); //<5>
}
