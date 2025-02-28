#include <algorithm>
#include <cassert>  //<1>

#include "analysis.h"  //<2>

namespace stock_prices //<3>
{
    std::vector<double> remove_invalid(std::vector<double> prices)  //<4>
    {
        std::remove_if(prices.begin(), prices.end(), negative);
        return prices;	
    }

    void test_analysis()  //<5>
    {
        auto got = remove_invalid({-1.2, 3.5}); //<6>
        assert(got.size() == 1);
        assert(got[0] == 3.5);
    }
}

