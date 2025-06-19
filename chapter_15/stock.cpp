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
 
