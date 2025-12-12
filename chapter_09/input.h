#pragma once

#include <expected>
#include <functional>
#include <istream>
#include <string>
#include <vector>

namespace stock_prices
{
    //std::expected<double, std::string> get_number(std::istream & input_stream);

    std::vector<double> get_prices(std::istream & input_stream,
		    std::function<void ()> prompt);

    std::vector<double> get_prices(double price, size_t count);
    std::vector<double> get_prices(double price, size_t count, double volatility);
    std::vector<double> get_prices(double price, size_t count,
		    std::function<double()> next_price);

    void test_input();
} 
