#include <type_traits> //<1>

#include "stock.h"

void stock_prices::test_stock() //<2>
{
    using namespace stock_prices;
    static_assert(std::is_abstract<Asset>()); //<3>
    static_assert(std::is_polymorphic<Asset>()); //<4>
    static_assert(std::is_polymorphic<Stock>()); //<5>
}

stock_prices::Stock::Stock( //<1>
        const std::string & stock_name,
        double start_price,
        double start_volatility) 
    : name(stock_name), 
        last_price(start_price), 
        volatility(start_volatility),
        gen(std::random_device{}())
{
}


double stock_prices::Stock::next_price() //<2>
{
    double percent  = volatility * distrib(gen); 
    last_price += last_price * percent; 
    return last_price;
}
 
