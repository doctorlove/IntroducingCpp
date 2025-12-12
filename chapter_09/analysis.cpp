#include <algorithm>
#include <cassert>
#include <numeric>
#include <stdexcept>

#include "analysis.h"

namespace stock_prices
{
    std::vector<double> remove_invalid(std::vector<double> prices)
    {
        auto new_end = std::remove_if(prices.begin(), prices.end(), negative);
        prices.erase(new_end, prices.end());
        return prices;    
    }

    double average(const std::vector<double> & prices)
    {
        if(prices.empty())
            throw std::invalid_argument("Prices cannot be empty");
        return std::accumulate(prices.begin(), prices.end(), double{})/prices.size();
    }

    double profit_on_first_uptick(const std::vector<double> & prices)
    {
        if(prices.empty())
            throw std::invalid_argument("Prices cannot be empty");
	const double first = prices.front();
        auto where = std::ranges::find_if(prices, 
			    [first] (double price)
			    {
			       return price > first;
			    }
			);
        if(where != prices.end())
        {
            return *where - first;
        }
        else
        {
            return 0.0;
        }
    }

    bool required_profit_possible(const std::vector<double> & prices, double required_profit)
    {
        const double first = prices.front();
        auto where = std::ranges::find_if(prices,
                            [first, required_profit] (double price)
                            {
                               return (price - first) >= required_profit;
                            }
                        );
        return where != prices.end();
    }

    void test_analysis() 
    {
        auto got = remove_invalid({-1.2, 3.5});
        assert(got.size() == 1);
        assert(got[0] == 3.5);

        try
        {
            average({});
            assert(false);
        }
        catch(const std::exception &)
        {
        }

        assert(average({1.0})==1.0);
    }
}

