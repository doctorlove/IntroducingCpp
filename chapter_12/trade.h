#include <memory>
#include <vector>

#include "stock.h"

namespace stock_prices
{
    class Exchange
    {
        double initial_funds{};
        double funds{ initial_funds };
        int number_of_assets{};
        std::unique_ptr<Stock> asset{}; 
        std::vector<double> prices{};

        public:
	Exchange(int number_of_assets, std::unique_ptr<Stock> asset) //<1>
            : number_of_assets(number_of_assets), asset(std::move(asset)) //<2>
	{
	}
        explicit Exchange(int number_of_assets) //<3>
            : Exchange(number_of_assets, nullptr) //<4>
        {
        }
        double next_price();
        std::vector<double> get_prices() const
        {
            return prices;
        }
    };

    void test_trades();
}
