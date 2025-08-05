#pragma once

#include <string>

namespace stock_prices
{
    class Asset
    {
    public:
        virtual ~Asset() = default;
        virtual std::string get_name() const = 0;
        virtual double get_price() const = 0;
        virtual double next_price() = 0;
    };
}