#include <cassert>
#include <format>
#include <iostream>
#include <print>

#include "events.h" //<1>
#include "trade.h"

double stock_prices::trading_game(Exchange & exchange)
{
    const double initial_funds{ 100.0 };
    double funds{ initial_funds };
    int number_of_shares{};

    bool playing{ true };
    while(playing)
    {
        auto status = std::format("Funds ${:.2f}, Shares {}",
            funds, number_of_shares);
        std::println("{}", status);
	const auto price = exchange.next_price();
        auto price_message = std::format("Current price: ${:.2f}", price);
        std::println("{: >{}}", price_message, status.size());
        std::println("Press (s) to sell, (b) to buy, (q) to quit");
        std::print("or something else to continue>");
        char choice{};
        std::cin >> choice;

        if (choice == 's')
        {
            if (number_of_shares > 0)
            {
                exchange.fulfill_sell_order();
                --number_of_shares;
                funds += price;
            }
            else
            {
		std::println("No stock to sell");
            }
        }
        else if (choice == 'b')
        {
            if (price <= funds)
            {
                exchange.fulfill_buy_order();
                ++number_of_shares;
                funds -= price;
            }
            else
            {
                std::println("Insufficient funds");
            }
        }
        else if (choice == 'q')
        {
            playing = false;
        }
	std::visit(EventVisitor{funds}, generate_event());//<2>
    }
    return funds - initial_funds;
}

double stock_prices::Exchange::next_price()
{
    if (!asset)
    {
        throw std::invalid_argument{"No asset available"};
    }
    prices.push_back(asset->get_price());
    return asset->next_price();
}

void stock_prices::test_trades()
{
    Exchange exchange{ 100 };
    try
    {
        exchange.next_price();
        assert(false);
    }
    catch (const std::exception & )
    {

    }

    static_assert(!std::is_copy_constructible<Exchange>());
    static_assert(!std::is_copy_assignable<Exchange>());

//    Exchange exchange_with_asset{100, std::make_unique<Stock>("Coffee", 4.8, 0.0113) };
 //   assert(exchange_with_asset.get_prices().empty());
//    exchange_with_asset.next_price();
//    assert(exchange_with_asset.get_prices().size() == 1);

}
