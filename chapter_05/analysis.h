#pragma once //<1>
#include <vector>

namespace stock_prices //<2>
{
    inline bool negative(double value) //<3>
    {
        return value < 0.0;
    }
    std::vector<double> remove_invalid(std::vector<double> prices);
    double average(const std::vector<double> & prices);
    void test_analysis();
} 
