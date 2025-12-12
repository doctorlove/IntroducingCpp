#pragma once

#include <random>
#include <string>

namespace stock_prices
{
    class Stock
    {
        std::string name{}; //<1>
        double last_price{}; //<1>
        double volatility{}; //<1>
        std::default_random_engine gen{std::random_device{}()}; //<1>
        std::normal_distribution<double> distrib{}; //<1>

    public:
        Stock(const std::string & stock_name,
            double start_price,
            double start_volatility); //<2>

        std::string get_name() const //<3>
        {
            return name;
        }

        double next_price(); //<4>
    };
}
