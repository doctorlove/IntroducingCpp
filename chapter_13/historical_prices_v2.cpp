#include "historical_prices.h"

double stock_prices::HistoricalPrices::next_price()
{
    ++index; //<1>
    return get_price(); //<2>
}

double stock_prices::HistoricalPrices::get_price() const
{
    if (index == prices.size()) //<3>
    {
	throw no_more_prices{}; //<4>
    }
    return prices[index]; //<5>
}
