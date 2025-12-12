#include <type_traits> //<1>

#include "asset.h"

void stock_prices::test_asset() //<2>
{
    using namespace stock_prices;
    static_assert(std::is_abstract<Asset>()); //<3>
}
