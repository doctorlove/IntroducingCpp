#pragma once

#include <concepts> //<1>
#include <expected>
#include <istream>
#include <string>
#include <vector>

namespace stock_prices
{
    std::expected<double, std::string> get_number(std::istream & input_stream);

    std::vector<double> get_prices(std::istream & input_stream,
            std::invocable<> auto prompt) //<2>
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

    void test_input();
} 
