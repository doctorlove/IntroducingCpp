#include <cassert>
#include <iostream>
#include <memory>
#include <print>
#include <vector>

#include "stock.h"

// want some polymorphism (12)
// and smart pointers (13)
// want the trading game
// want a format method for the Stock class (15)
// want to find a way to use a std::variant (14)

// from main.cpp in chapter 9
//maybe buy, sell, quit
// maybe a Trader and a Bot
//maybe best profit and worst loss?
void trading_game_original(const std::vector<double>& prices)
{
    const double initial_funds{ 100.0 };
    double funds{ initial_funds };
    int number_of_shares{};

    for (auto price : prices)
    {
        auto status = std::format("Funds ${:.2f}, Shares {}",
            funds, number_of_shares);
        std::println("{}", status);
        auto price_message = std::format("Current price: ${:.2f}", price);
        std::println("{: >{}}", price_message, status.size());
        std::println("Press (s) to sell, (b) to buy");
        std::print("or something else to continue>");
        char choice{};
        std::cin >> choice;

        if (choice == 's')
        {
            if (number_of_shares > 0)
            {
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
                ++number_of_shares;
                funds -= price;
            }
            else
            {
                std::println("Insufficient funds");
            }
        }
    }
    std::println("Total profit ${:.2f}", funds - initial_funds);
    std::println("Game over");
}

void chapter_11()
{
    using namespace stock_prices;
    std::vector<Stock> stocks;
    stocks.push_back(Stock{"Coffee", 4.8, 0.0113});

    for(auto & stock : stocks)
    {
        std::cout << stock.get_name() << ": " << stock.next_price() << '\n';
    }
}


void chapter_13()
{
    // polymorphism means a new base class... 
    // and public/private inheritence
    // and override
    // some tests too would be nice
    using namespace stock_prices;
    //const Asset& asset{ Stock{"Coffee", 4.8, 0.0113} }; // has to be const
    auto coffee{ Stock{ "Coffee", 4.8, 0.0113 } };
    Asset& volatile_asset{ coffee }; // more details on references
    auto bond{ Bond{ "FixedRateBond", 100.0, 0.04 } };
    Asset& fixed_rate_asset{bond};
    // Slicing - but might not be clear without an intermediary non-abstract class

    std::cout << volatile_asset.get_name() << ": " << volatile_asset.next_price() << '\n';
    std::cout << fixed_rate_asset.get_name() << ": " << fixed_rate_asset.next_price() << '\n';
    // Introduce how to test and do this in depth

    // vector of various stock

    // trading game?
    // Was in Example 7-2. A trading game first
    // Then Example 9-1. The new trading game
    // also in main
    // 
}

void chapter_12()
{
    using namespace stock_prices;
    auto asset{ std::make_unique<Stock>("Coffee", 4.8, 0.0113) };
    std::cout << (*asset).get_name() << ": " << asset->next_price() << '\n';
    std::cout << asset->get_name() << ": " << asset->next_price() << '\n';

    // then put in vector
    std::vector<std::unique_ptr<Asset>> assets; // reserve?
    assets.push_back(std::make_unique<Stock>("Coffee", 4.8, 0.0113));

    int value{ 42 };
    int * pointer_to_value = &value;
    int & reference_to_value = value;

    std::cout << "value " << value
        << ", pointer " << *pointer_to_value
        << ", reference " << reference_to_value << '\n';
    reference_to_value = 101;
    std::cout << "value " << value
        << ", pointer " << *pointer_to_value
        << ", reference " << reference_to_value << '\n';

    //auto try_to_copy{asset};

    //auto moved_asset{ asset.release() };
    //assert(asset == nullptr);
    auto another_moved_asset{ std::move(asset) };
    assert(asset == nullptr);
//    another_moved_asset.release();
}

void chapter_14()
{
    // trading game against a bot?
    // std::variant for bot/player?
    // or maybe a std::optional, but an optional price seems silly
    // would a visit to a buy/sell work? But that needs to mutate state

    //https://www.cppstories.com/2018/06/variant/ does say polymorphism without vtables
}

void chapter_15()
{
    //std::formatter
    using namespace stock_prices;
    auto coffee{ Stock{ "Coffee", 4.8, 0.0113 } };
}

int main()
{
    chapter_11();
    chapter_12();
    chapter_13();
}
