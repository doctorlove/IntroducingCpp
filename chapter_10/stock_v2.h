#pragma once

#include <string>

namespace stock_prices
{
    class Stock
    {
        std::string name{}; //<1>
        double last_price{};
        double volatility{};

    public: //<2>
        std::string get_name() const //<3>
        {
            return name;
        }
        void set_name(const std::string & new_name) //<4>
        {
            name = new_name;
        }
    };
}


