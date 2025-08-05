#include <cassert>
#include <format>
#include <iostream>
#include <print>

#include "trade.h"

double stock_prices::trading_game(Exchange & exchange)
{
    const double initial_funds{ 100.0 };
    double funds{ initial_funds };
    int number_of_shares{};

    bool playing{ true }; //<1>
    while(playing) //<2>
    {
        auto status = std::format("Funds ${:.2f}, Shares {}",
            funds, number_of_shares);
        std::println("{}", status);
	    const auto price = exchange.next_price(); //<3>
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
                exchange.fulfill_sell_order(); //<4>
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
                exchange.fulfill_buy_order(); //<5>
                ++number_of_shares;
                funds -= price;
            }
            else
            {
                std::println("Insufficient funds");
            }
        }
        else if (choice == 'q') //<6>
        {
            playing = false;
        }
    }
    auto profit = funds - initial_funds;
    std::println("Total profit ${:.2f}", profit);
    std::println("Game over");
    return profit;
}

double stock_prices::Exchange::next_price()
{
    if (!asset)
    {
        throw std::invalid_argument{"No asset available"};
    }
    prices.push_back(asset->get_price()); // save last one
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

    Exchange exchange_with_asset{100, std::make_unique<Stock>("Coffee", 4.8, 0.0113) };
    assert(exchange_with_asset.get_prices().empty());
    exchange_with_asset.next_price();
    assert(exchange_with_asset.get_prices().size() == 1);

}
