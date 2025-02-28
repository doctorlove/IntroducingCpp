#include <algorithm>
#include <cassert>
#include <numeric>
#include <stdexcept>

#include "analysis.h"

namespace stock_prices
{
    std::vector<double> remove_invalid(std::vector<double> prices)
    {
        auto new_end = std::remove_if(prices.begin(), prices.end(), negative);  //<1>
        prices.erase(new_end, prices.end());  //<2>
        return prices;	
    }

    double average(const std::vector<double> & prices)
    {
	if(prices.empty())
            throw std::invalid_argument("Prices cannot be empty");
        return std::accumulate(prices.begin(), prices.end(), double{})/prices.size();
    }

    void test_analysis() 
    {
        auto got = remove_invalid({-1.2, 3.5});
        assert(got.size() == 1);
        assert(got[0] == 3.5);

	try
	{
            average({});  //<1>
	    assert(false);  //<2>
	}
	catch(const std::exception &) //<3>
	{
	}

	assert(average({1.0})==1.0); //<4>
    }
}

