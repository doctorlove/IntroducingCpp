#include <algorithm> //<1>
#include <iostream>
#include <vector>

#include "input.h"

// get_prices as before //<2>

std::vector<double> get_prices(std::istream & input_stream)
{
    std::cout << "Please enter some numbers.\n>";
    std::vector<double> numbers{};
    auto number = stock_prices::get_number(input_stream);
    while(number.has_value())
    {
        numbers.push_back(number.value());
        std::cout << '>';
        number = stock_prices::get_number(input_stream);
    }
    return numbers;
}

int main()
{
    auto prices = get_prices(std::cin);
    if(!prices.empty()) //<3>
    {
        auto result = std::ranges::minmax(prices); //<4>
        std::cout << "min " << result.min << '\n'; //<5>
        std::cout << "max " << result.max << '\n'; //<6>
    }
}

