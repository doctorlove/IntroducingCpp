#include "stock.h"

stock_prices::Stock::Stock(
        const std::string & stock_name,
        double start_price,
        double start_volatility) 
    : name(stock_name), 
        last_price(start_price), 
        volatility(start_volatility),
        gen(std::random_device{}())
{
}


double stock_prices::Stock::next_price()
{
    double percent  = volatility * distrib(gen); 
    last_price += last_price * percent; 
    return last_price;
}

double stock_prices::Bond::next_price()
{
    last_price *= 1.0 + percent; // should really be time based, like interest once a year, but std::chrono is hard
    // could maybe do every n-th tick instead? 
    return last_price;
}

