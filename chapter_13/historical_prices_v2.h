#include <string>
#include <vector>

#include "asset.h"

namespace stock_prices
{
    class HistoricalPrices : public Asset
    {
        std::string name{};
        std::vector<double> prices{};
        size_t index{0};

    public:
        explicit HistoricalPrices(const std::vector<double> & prices)
            : prices(prices)
        {
        }
        std::string get_name() const override
        {
            return name;
        }

        double get_price() const override;

        double next_price() override;
    };
}
