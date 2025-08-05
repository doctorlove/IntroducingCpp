#include <exception>
#include "stock.h"

namespace stock_prices
{
    class no_more_prices : public std::exception 
    {
    };

    class HistoricalPrices : public Asset
    {
        std::string name{};
        std::vector<double> prices{};
        size_t index{0};

    public:
        HistoricalPrices(const std::vector<double> & prices)
            : prices(prices)
        {
        }
        std::string get_name() const override
        {
            return name;
        }

        double get_price() const override
        {
            if (index == prices.size())
            {
                throw no_more_prices{};
            }
            return prices[index];
        }

        double next_price() override
        {
            ++index;
            return get_price();
        }
    };
}
