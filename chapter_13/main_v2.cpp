#include "stock.h"
#include "trade.h"

int main()
{
using namespace stock_prices;
    test_stock();
    test_trades();

    std::unique_ptr<Asset> asset{
        std::make_unique<Stock>("Coffee", 4.8, 0.0113)
    };
    Exchange exchange{1, std::move(asset)};
}
