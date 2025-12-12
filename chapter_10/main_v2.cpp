#include <iostream>
#include <vector>

#include "stock.h"

int main()
{
    using namespace stock_prices;
    std::vector stocks { //<1>
        Stock{"Coffee", 4.8, 0.0113}, //<2>
        Stock{"Tea", 171.68, 0.023}, //<2>
        Stock{"Sugar", 17.91, 0.05}
    };

    for(const auto & stock: stocks)
    {
        std::cout 
          << stock.get_name()  //<3>
          << '\n';
    }
}
