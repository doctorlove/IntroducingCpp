#include <cassert>
#include <stdexcept>
#include <type_traits>

#include "trade.h"

double stock_prices::Exchange::next_price()
{
    if (!asset)
    {
        throw std::invalid_argument{"No asset available"};
    }
    prices.push_back(asset->get_price());
    return asset->next_price();
}

void stock_prices::test_trades()
{
    Exchange exchange{ 100 };
    try
    {
        exchange.next_price();
        assert(false);
    }
    catch (const std::exception & )
    {

    }

    static_assert(!std::is_copy_constructible<Exchange>());
    static_assert(!std::is_copy_assignable<Exchange>());

    Exchange exchange_with_asset{100, std::make_unique<Stock>("Coffee", 4.8, 0.0113) };
    assert(exchange_with_asset.get_prices().empty());
    exchange_with_asset.next_price();
    assert(exchange_with_asset.get_prices().size() == 1);

}
