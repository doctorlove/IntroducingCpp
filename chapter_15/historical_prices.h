#include <string>
#include <vector>

#include "asset.h"

namespace stock_prices
{
    class HistoricalPrices : public Asset //<1>
    {
        std::string name{};
        std::vector<double> prices{};
        size_t index{0}; //<2>

    public:
        explicit HistoricalPrices(const std::vector<double> & prices) //<3>
            : prices(prices)
        {
        }
        std::string get_name() const override //<4>
        {
            return name;
        }

        double get_price() const override;

        double next_price() override;
    };
}
