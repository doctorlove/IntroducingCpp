#pragma once

#include <expected>
#include <functional> //<1>
#include <istream>
#include <string>
#include <vector> //<2>

namespace stock_prices
{
    std::expected<double, std::string> get_number(std::istream & input_stream);
    std::vector<double> get_prices(std::istream & input_stream,
		    std::function<void ()> prompt); //<3>

    void test_input(); //<4>
} 
