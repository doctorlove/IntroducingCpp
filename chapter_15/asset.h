#pragma once

#include <exception> //<1>
#include <string>

namespace stock_prices
{
    class Asset
    {
    public:
        virtual ~Asset() = default; //<1>
        virtual std::string get_name() const = 0; //<2>
        virtual double get_price() const = 0; //<3>
        virtual double next_price() = 0; //<4>
    };

    class no_more_prices : public std::exception //<2>
    {
    };

    void test_asset();
}
