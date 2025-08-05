#include <cassert>
#include <iomanip>
#include <iostream>
#include <memory>
#include <print>
#include <string>
#include <type_traits>
#include <vector>

#include "historical_prices.h"
#include "stock.h"
#include "trade.h"

void tests()
{
    using namespace stock_prices;
    assert(std::format("Price {}", Price{ 100 }) == "Price $100.00");
    assert(std::format("Price {:£}", Price{ 100 }) == "Price £100.00");

    static_assert(std::is_abstract<Asset>());
    static_assert(std::is_polymorphic<Asset>());
    static_assert(std::is_polymorphic<Stock>());
}

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


void trading_game(std::vector<std::unique_ptr<stock_prices::Asset>> & assets)
{
    for (auto& asset : assets)
    {
        std::cout << asset->get_name() << ": " << asset->next_price() << '\n';
    }

    const double initial_funds{ 100.0 };
    double funds{ initial_funds };
    int number_of_shares{}; // in what though? NEED a std::map, surely?
    // or a vector and zip them (kinda) or just use the same index
    bool playing = true;

    while(playing)
    {
        // TODO change assets to use a Price
        auto status = std::format("Funds ${:.2f}, Shares {}",
            funds, number_of_shares);
        std::println("{}", status);
        for (auto& asset : assets)
        {
            auto price = asset->next_price();
            std::cout << asset->get_name() << ": " << price << '\n'; //println instead

            auto price_message = std::format("Current price: ${:.2f}", price);
            std::println("{: >{}}", price_message, status.size());

            std::println("Press (s) to sell, (b) to buy (q) to quite game");
            std::print("or something else to continue>");
            char choice{};
            std::cin >> choice;

            if (choice == 's')
            {
                if (number_of_shares > 0) // shared in what though?
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
            else if (choice =='q')
            {
                playing = false;
            }
        }
    }
    std::println("Total profit ${:.2f}", funds - initial_funds);
    std::println("Game over");
}

struct no_op_deleter
{
    void operator()(auto value) const
    {
        std::cout << "Nothing to do for " << *value << "\n";
    }
};

void chapter_12()
{
    using namespace stock_prices;
    auto asset{ std::make_unique<Stock>("Coffee", 4.8, 0.0113) };
    std::cout << (*asset).get_name() << ": " << asset->next_price() << '\n';
    std::cout << asset->get_name() << ": " << asset->next_price() << '\n';
    asset.reset(std::make_unique<Stock>("Tea", 4.8, 0.0113).release()); //!

    auto moved_asset{ std::move(asset) };
    auto another_moved_asset{ moved_asset.release() };
    delete another_moved_asset;

    // then put in vector
    std::vector<std::unique_ptr<Asset>> assets; // reserve?
    assets.push_back(std::make_unique<Stock>("Coffee", 4.8, 0.0113));

    auto shared_asset{ std::make_shared<Stock>("Coffee", 4.8, 0.0113) };
    auto joint_asset{ shared_asset };

    std::weak_ptr just_looking{ joint_asset };
    if (auto now_using = just_looking.lock())
    {
        std::cout << "Using the shared pointer\n";
    }
    else
    {
        std::cout << "Unable to use the shared pointer\n";
    }

    int value{ 42 };
    int* pointer_to_value = &value;
    int& reference_to_value = value;

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
    //auto another_moved_asset{ std::move(asset) };
    //    assert(asset == nullptr);
    //    another_moved_asset.release();


/*
Add a little example that uses the std::unique_ptr more
exensively: std::make_unique to create it, member access operators to access some value,
move to another std::unique_ptr, which is potentially a class member, and finally the destructors
of all unique_ptrs, one deleting the resource, the others do not
*/
    //auto smart_pointer_to_value{ std::make_unique<int, no_op_deleter>(&value)}; 
    // can't provide custom deleter for unqiue ptr
    std::unique_ptr<int, no_op_deleter> smart_pointer_to_value{ &value };

    stock_prices::test_trades();
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
    // want a from file too
    Asset& volatile_asset{ coffee }; // more details on references

    std::cout << volatile_asset.get_name() << ": " << volatile_asset.next_price() << '\n';
    // Introduce how to test and do this in depth

    // vector of various stock

    // some testing too?
    // need type_traits
    static_assert(std::is_abstract<Asset>());
    static_assert(std::is_polymorphic<Asset>());
    static_assert(std::is_polymorphic<Stock>());
    // note
    // https://en.cppreference.com/w/cpp/utility/format/formatter.html
    // has type traits mentioned

    // TODO what's the best way to do this?
    std::vector<std::unique_ptr<Asset>> assets;
    assets.emplace_back(std::make_unique<Stock>("Coffee", 100.0, 0.25));
    /// or just make the stock maybe go up loads?

    // could have a historical asset using a file of prices (asset name is filename)

    // Also
    //https://stackoverflow.com/questions/3283778/why-can-i-not-push-back-a-unique-ptr-into-a-vector
    // if we make it first, we have an lavlue so would need to move
    // How would emplace work when I need to specify the type?

    // Aside, 
    // https://www.sandordargo.com/blog/2023/04/12/vector-of-unique-pointers to avoid copies from an initializer list

    //// no raw loops
    //for (int i=0; i<100; ++i)
    //{
    //    for (auto& asset : assets)
    //    {
    //        std::cout << asset->get_name() << ": " << asset->next_price() << '\n';
    //    }
    //}
    // 

    std::unique_ptr<Asset> asset{ std::make_unique<Stock>("Coffee", 4.8, 0.0113) };
    Exchange exchange{ 1, std::move(asset) };
    trading_game(exchange);
    // nah - just one asset
    // TODO 
    //cautious bot picking bonds
    // reckless... waiting out for a big profit?

    

    // trading game?
    // Was in Example 7-2. A trading game first
    // Then Example 9-1. The new trading game
    // also in main
    // 
}

#include <variant>

struct Nothing
{
};

struct FixedFine
{
    double fine{};
};

struct Gift
{
    double gift{};
};

struct InterestPayment
{
    double percent{};
};

using Event = std::variant<Nothing, FixedFine, Gift, InterestPayment, std::string>;
// maybe string too, for a message?

template<class... Ts>
struct overloads : Ts... { using Ts::operator()...; }; // TODO can I do this without the overloads?

struct EventVisitor
{
    double & funds; // might need to discuss a dangling ref now
    void operator()(Nothing) {};
    void operator()(FixedFine event) { funds -= event.fine; };
    void operator()(Gift event) { funds += event.gift; };
    void operator()(InterestPayment event) { funds *= (1.0 + event.percent); };
    void operator()(std::string message) { std::cout << message << '\n'; }// Can I not do a const & here?
};

void chapter_14()
{
    // events
    // Can I not do a const & here?
    double funds{ 0.0 };
    const auto visitor = overloads
    {
        [&funds](Nothing) {},
        [&funds](FixedFine event) { funds -= event.fine; },
        [&funds](Gift event) { funds += event.gift; },
        [&funds](InterestPayment event) { funds *= (1.0+event.percent); },
        [](std::string message) { std::cout << message << '\n'; }
    };
    Event event{ Gift{ 25.00 } };
    //std::visit(visitor, event);
    std::visit(EventVisitor{funds}, event);
    // have a news item too?

    // add "surprise" function to pick an event at random
    // in the trading game
    // vector of variants
    // using maybe random shuffle and pick first?


    // trading game against a bot?
    // std::variant for bot/player?
    // or maybe a std::optional, but an optional price seems silly
    // would a visit to a buy/sell work? But that needs to mutate state

    //https://www.cppstories.com/2018/06/variant/ does say polymorphism without vtables

    // maybe a cache? (mention in chapter 12)

    // or maybe a dividend payout for any Stock
}

void chapter_15()
{
    //std::formatter
    using namespace stock_prices;
    auto coffee{ Stock{ "Coffee", 4.8, 0.0113 } };
}

int main()
{
    tests();

    chapter_11();
    chapter_12();
    chapter_13();
    chapter_14();

    std::println("{:GBP}", stock_prices::Price{ 100.123 });

}
