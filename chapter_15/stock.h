#pragma once

#include <random>
#include <string>

namespace stock_prices
{
    class Asset
    {
    public:
        virtual ~Asset() = default;
        virtual std::string get_name() const = 0;
        virtual double next_price() = 0;
    };

    class Stock: public Asset
    {
        std::string name{}; 
        double last_price{}; 
        double volatility{}; 
        std::default_random_engine gen; // TODO how to test
        std::normal_distribution<double> distrib; 

    public:
        Stock(const std::string & stock_name,
            double start_price,
            double start_volatility);

        Stock(const Stock & other) = delete;
        Stock(Stock && other) noexcept = default;

        Stock & operator = (const Stock & other) = delete;
        Stock & operator = (Stock && other) noexcept = default;

        std::string get_name() const override
        {
            return name;
        }

        double next_price() override;
    };

    class Bond : public Asset
    {
        std::string name{};
        double last_price{};
        double percent;
    public:
        Bond(const std::string & name,
            double start_price,
            double percent) : name(name), last_price(start_price), percent(percent)
        {
        }

        std::string get_name() const override
        {
            return name;
        }

        double next_price() override;
    };
}
