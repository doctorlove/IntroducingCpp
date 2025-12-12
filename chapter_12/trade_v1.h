#include <memory>
#include <vector>

#include "stock.h"

namespace stock_prices
{
    class Exchange //<1>
    {
        double initial_funds{}; //<2>
        double funds{ initial_funds }; //<3>
        int number_of_assets{}; //<4>
        std::unique_ptr<Stock> asset{}; //<5>
        std::vector<double> prices{}; //<6>

        public:
        Exchange(int number_of_assets)
            : number_of_assets(number_of_assets) //<7>
        {
        }
        double next_price(); //<8>
        std::vector<double> get_prices() const //<9>
        {
            return prices;
        }
    };
}
