#include <algorithm>
#include <cassert>
#include <limits>
#include <random>
#include <sstream>

#include "input.h"

namespace stock_prices
{
    std::expected<double, std::string> get_number(std::istream & input_stream)
    {
        double number{};
        input_stream >> number;
        if(input_stream)
        {
            return number;
        }
        input_stream.clear(); 
        input_stream.ignore( 
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
        return std::unexpected{"That's not a number"};
    }

    std::vector<double> get_prices(std::istream & input_stream,
            std::function<void ()> prompt)
    {
        prompt();
        std::vector<double> numbers{};
        auto number = stock_prices::get_number(input_stream);
        while(number.has_value())
        {
            numbers.push_back(number.value());
            prompt();
            number = stock_prices::get_number(input_stream);
        }
        return numbers;
    }

    std::vector<double> get_prices(double price,
                   size_t count)
    {
        std::vector<double> prices(count);
        const double step = price/100.0;

        std::random_device rd{};
        std::default_random_engine gen{rd()};
        std::uniform_int_distribution distrib{-1, +1};

        auto next_price = [step, &price, &gen, &distrib]() 
        {
            price += step*distrib(gen);
            return price;
        };
        std::ranges::generate(prices.begin(), prices.end(), next_price);
        return prices;
    }

    std::vector<double> get_prices(double price, size_t count, double volatility)
    {
        std::vector<double> prices(count); //<1>

        std::random_device rd{}; //<2>
        std::default_random_engine gen{rd()}; //<2>
        std::normal_distribution distrib; //<3>

        auto next_price = [volatility, &price, &gen, &distrib]() 
        {
            double percent  = volatility * distrib(gen); //<4>
            price += price * percent; //<5>
            return price;
        };
        std::ranges::generate(prices.begin(), prices.end(), next_price); //<6>
        return prices;
    }

    std::vector<double> get_prices(double price, size_t count,
		    std::function<double()> next_price)
    {
        std::vector<double> prices(count);

        std::ranges::generate(prices.begin(), prices.end(), next_price);
        return prices;
    }
    
    std::vector<double> get_prices_improved(double price, size_t count,
		    std::function<double()> next_price)
    {
        std::vector<double> prices{};
        prices.reserve(count);

        std::ranges::generate_n(std::back_inserter(prices),
                                count, next_price);
        return prices;
    }
    
    void test_input()
    {
        std::stringstream no_input{""};
        auto no_op = [](){};
        assert(get_prices(no_input, no_op).empty());

        std::stringstream some_input{"1"};
        assert(get_prices(some_input, no_op).size() == 1);

        auto random_prices = get_prices(100.0, 10);
        assert(random_prices.size() == 10);

        auto random_prices_normal = get_prices(100.0, 10, 0.05);
        assert(random_prices_normal.size() == 10);

        std::random_device rd{};
        std::default_random_engine gen{rd()};
        std::normal_distribution distrib;
        double price = 100.0;
        const double volatility = 0.05;
        auto next_price = [volatility, &price, &gen, &distrib]() 
        {
            double percent  = volatility * distrib(gen);
            price += price * percent;
            return price;
        };
        const auto more_prices = stock_prices::get_prices_improved(100.0, 10, next_price);
        assert(more_prices.size() == 10);
    }
}



