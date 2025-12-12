#pragma once

#include <random>
#include <string>

#include "asset.h" //<1>

namespace stock_prices
{
    class Stock: public Asset //<2>
    {
        std::string name{}; 
        double last_price{}; 
        double volatility{}; 
        std::default_random_engine gen;
        std::normal_distribution<double> distrib; 

    public:
        Stock(const std::string & stock_name,
            double start_price,
            double start_volatility);

        Stock(const Stock & other) = delete;
        Stock(Stock && other) noexcept = default;

        Stock & operator = (const Stock & other) = delete;
        Stock & operator = (Stock && other) noexcept = default;

        std::string get_name() const override //<3>
        {
            return name;
        }

        double get_price() const override //<4>
        {
            return last_price;
        }

        double next_price() override; //<5>
    };
}

