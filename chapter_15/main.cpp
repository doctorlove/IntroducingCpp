#include <iostream>

#include "events.h"

int main()
{
    auto hasher = std::hash<stock_prices::Nothing>{};
    std::cout << hasher(stock_prices::Nothing()) << '\n';
}

