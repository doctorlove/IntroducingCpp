#pragma once

#include <string>

namespace stock_prices
{
    class Stock
    {
        std::string name{};
        double last_price{};
        double volatility{};

    public:
        Stock(const std::string & stock_name,
            double start_price,
            double start_volatility) //<1>
        : //<2>
            name(stock_name), //<2>
            last_price(start_price), //<2>
            volatility(start_volatility) //<2>
        {
        }

        std::string get_name() const //<3>
        {
            return name;
        }
    };
}


