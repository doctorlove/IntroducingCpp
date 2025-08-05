#pragma once

#include <memory>

#include "stock.h"

namespace stock_prices
{
    class Exchange
    {
        double initial_funds{100.0};
        double funds{ initial_funds };
        int number_of_assets{};
        std::unique_ptr<Asset> asset{}; //<1>
        std::vector<double> prices{};

        public:
        Exchange(int number_of_assets, std::unique_ptr<Asset> asset) //<2>
            : number_of_assets(number_of_assets), asset(std::move(asset))
        {
        }
        explicit Exchange(int number_of_assets)
            : Exchange(number_of_assets, nullptr)
        {
        }
        double next_price();
        std::vector<double> get_prices() const
        {
            return prices;
        }

        void fulfill_buy_order()
        {
            --number_of_assets;
	        funds += asset->get_price();
        }

        void fulfill_sell_order()
        {
            ++number_of_assets;
	        funds -= asset->get_price();
        }
    };

    void test_trades();

    double trading_game(Exchange & exchange);
}
