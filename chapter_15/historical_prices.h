#include <string>
#include <vector>

#include "stock.h"

namespace stock_prices
{
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
            return prices[index];
        }

        double next_price() override
        {
            ++index;
            if (index == prices.size())
            {
                // TODO throw
            }
            return prices[index];
        }
    };
    // and a historical prices
    //Example 8 - 2. Reading prices from a file
    //    void read_from_file(const std::string & filename)
    //{
    //    std::ifstream file{ filename };
    //    if (file)
    //    {
    //        auto prices = stock_prices::get_prices(file, []() {});
    //        for (auto price : prices)
    //        {
    //            std::cout << price << '\n';
}
