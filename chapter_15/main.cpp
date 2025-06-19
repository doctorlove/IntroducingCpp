#include <iostream>
#include <memory>
#include <vector>

#include "stock.h"

// want some polymorphism (12)
// and smart pointers (13)
// want the trading game
// want a format method for the Stock class (15)
// want to find a way to use a std::variant (14)

void chapter_11()
{
    using namespace stock_prices;
    std::vector<Stock> stocks;
    stocks.push_back(Stock{"Coffee", 4.8, 0.0113});

    for(auto & stock : stocks)
    {
        std::cout << stock.get_name() << ": " << stock.next_price() << '\n';
    }
}


void chapter_12()
{
    // polymorphism means a new base class... 
    // and public/private inheritence
    // and override
    // some tests too would be nice
    using namespace stock_prices;
    //const Asset& asset{ Stock{"Coffee", 4.8, 0.0113} }; // has to be const
    auto coffee{ Stock{ "Coffee", 4.8, 0.0113 } };
    Asset& volatile_asset{ coffee }; // more details on references
    auto bond{ Bond{ "FixedRateBond", 100.0, 0.04 } };
    Asset& fixed_rate_asset{bond};
    // Slicing - but might not be clear without an intermediary non-abstract class

    std::cout << volatile_asset.get_name() << ": " << volatile_asset.next_price() << '\n';
    std::cout << fixed_rate_asset.get_name() << ": " << fixed_rate_asset.next_price() << '\n';
    // Introduce how to test and do this in depth
}

void chapter_13()
{
    using namespace stock_prices;
    auto asset{std::make_unique<Stock>("Coffee", 4.8, 0.0113 )};
    std::cout << asset->get_name() << ": " << asset->next_price() << '\n';

    // then put in vector

}

int main()
{
    chapter_11();
    chapter_12();
    chapter_13();
}
