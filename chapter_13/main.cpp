#include <iostream>
#include <memory> 

#include "stock.h"

int main()
{
using namespace stock_prices;
    auto coffee{ Stock{ "Coffee", 4.8, 0.0113 } }; //<1>
    Asset & asset{coffee}; //<2>
    std::cout << asset.get_name() << ": " << asset.next_price() << '\n'; //<3>

    std::unique_ptr<Asset> asset_pointer{
        std::make_unique<Stock>("Coffee", 4.8, 0.0113)
    }; //<4>
    std::cout << asset_pointer->get_name() << ": " 
        << asset_pointer->next_price() << '\n'; //<5>
}
