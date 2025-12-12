#pragma once

#include <random>
#include <string>

namespace stock_prices
{
    class Stock
    {
        std::string name{}; 
        double last_price{}; 
        double volatility{}; 
        std::default_random_engine gen; 
        std::normal_distribution<double> distrib; 

    public:
        Stock(const std::string & stock_name,
            double start_price,
            double start_volatility); //<1>

        Stock(const Stock & other) = delete; //<2>
        Stock(Stock && other) noexcept = default; //<3>

        Stock & operator = (const Stock & other) = delete; //<4>
        Stock & operator = (Stock && other) noexcept = default; //<5>

        std::string get_name() const //<6>
        {
            return name;
        }

        double next_price(); //<7>
    };
}
