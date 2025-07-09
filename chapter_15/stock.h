#pragma once

//#include <charconv> //from chars
#include <format>
#include <random>
#include <ranges>
#include <string>

namespace stock_prices
{
    class Price
    {
        double price{};
    public:
        explicit Price(double price)
            : price(price)
        {

        }

        double operator()() const
        { 
            return price; 
        }
    };

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

// Based on
//https://en.cppreference.com/w/cpp/utility/format/formatter.html

//https://www.cppstories.com/2022/custom-stdformat-cpp20/
// has
//template <>
//struct std::formatter<MyType> {
//    constexpr auto parse(std::format_parse_context& ctx) {
//        return /* */;
//    }
//
//    auto format(const MyType& obj, std::format_context& ctx) const {
//        return std::format_to(ctx.out(), /* */);
//    }
//};

template<>
struct std::formatter<stock_prices::Price, char>
{
    char currency_sign{ '$' };
    template<class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx)
    {
        // ctx is the stuff after a colon, so use {:£} etc
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        if (*it != '}')
        {
            currency_sign = *it;
            ++it;
        }
        if (it != ctx.end() && *it != '}')
            throw std::format_error("Invalid format args for Price.");

        return it;
    }

    template<class FmtContext>
    FmtContext::iterator format(const stock_prices::Price & price, FmtContext& ctx) const
    {
        return std::format_to(ctx.out(), "{}{:.2f}", currency_sign, price());
    }
};
