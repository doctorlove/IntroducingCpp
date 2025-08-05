#include <memory>
#include <vector>

#include "stock.h"

namespace stock_prices
{
	class Exchange
	{
		double initial_funds{};
		double funds{ initial_funds };
		int number_of_assets{};
		std::unique_ptr<Asset> asset{};
		std::vector<double> prices{};
	public:
		explicit Exchange(int number_of_assets)  // introduce explicit, show example without it
			: Exchange(number_of_assets, nullptr)
		{
		}
		Exchange(int number_of_assets, std::unique_ptr<Asset> asset)
			: number_of_assets(number_of_assets), asset(std::move(asset))
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
	double trading_game(Exchange& exchange);

}