#pragma once

#include <string>

namespace stock_prices
{
    struct Stock //<1>
    { //<2>
        std::string name{}; //<3>
        double last_price{}; //<4>
        double volatility{}; //<5>
    }; //<6>
}


