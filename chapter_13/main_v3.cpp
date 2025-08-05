#include <iostream>
#include <memory>

#include "historical_prices.h"
#include "stock.h"
#include "trade.h"

int main(int argc, char *argv[])
{
    using namespace stock_prices;
    test_stock();
    test_trades();

    std::unique_ptr<Asset> asset{
        std::make_unique<Stock>("Coffee", 4.8, 0.0113)
    };
    Exchange exchange{1, std::move(asset)};
    trading_game(exchange);

    std::cout << "Rerun? [y]es n[o]?\n";
    char choice;
    std::cin >> choice;
    if (choice == 'y')
    {
        try
        {
            Exchange historical_exchange{
                1,
                std::make_unique<HistoricalPrices>(exchange.get_prices())
            };
            trading_game(historical_exchange);
        }
        catch (const std::exception &)
        {
            std::cout << "Game over\n";
        }
    }
}
