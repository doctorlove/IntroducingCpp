#pragma once //<1>

#include <expected> //<2>
#include <istream> //<2>
#include <string> //<2>

namespace stock_prices //<3>
{
    std::expected<double, std::string> get_number(std::istream & input_stream); //<4>
} 
