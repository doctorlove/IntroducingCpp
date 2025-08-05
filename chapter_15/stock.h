#pragma once

#include <format>
#include <random>
#include <string>

namespace stock_prices
{
    class Price
    {
        double price{};
    public:
        explicit Price(double price) // Opportunity to ban negatives
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
        virtual double get_price() const = 0;
        virtual double next_price() = 0;
    };

    class Stock : public Asset
    {
        std::string name{};
        double last_price{};
        double volatility{};
        std::default_random_engine gen;
        std::normal_distribution<double> distrib;

    public:
        Stock(const std::string& stock_name,
            double start_price,
            double start_volatility);

        Stock(const Stock& other) = delete;
        Stock(Stock&& other) noexcept = default;

        Stock& operator = (const Stock& other) = delete;
        Stock& operator = (Stock&& other) noexcept = default;

        std::string get_name() const override
        {
            return name;
        }

        double get_price() const override
        {
            return last_price;
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

// seems to be calling the functions twice
// but Bartek mentioned that

template<>
struct std::formatter<stock_prices::Price, char>
{
    std::string currency_sign{ "$" };
    template<class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx)
    {
        // ctx is the stuff after a colon, so use {:£} etc
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        //if (*it != '}')
        //{
        //    currency_sign = *it;
        //    ++it;
        //}
        auto start = it;
        while (it != ctx.end() && *it != '}') ++it;

        if(start != it)
            currency_sign = std::string(start, it);

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
