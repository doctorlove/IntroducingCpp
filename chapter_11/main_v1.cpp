#include <vector>

#include "stock.h"

int main()
{
    using namespace stock_prices;
    std::vector<Stock> stocks;
    for(int i=0; i<10; ++i)
    {
        stocks.push_back({"Coffee", 10.1, 0.05});
    }
}
