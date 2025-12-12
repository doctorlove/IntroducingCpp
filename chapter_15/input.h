#pragma once

#include <expected>
#include <istream>
#include <string>
#include <vector>

namespace stock_prices
{
    std::expected<double, std::string> get_number(std::istream & input_stream);

    template<typename T>
    std::vector<double> get_prices(std::istream & input_stream,
            T prompt) //<1>
    {
        prompt(); //<2>
        std::vector<double> numbers{};
        auto number = stock_prices::get_number(input_stream);
        while(number.has_value())
        {
            numbers.push_back(number.value());
            prompt(); //<3>
            number = stock_prices::get_number(input_stream);
        }
        return numbers;
    }

    void test_input();
} 
