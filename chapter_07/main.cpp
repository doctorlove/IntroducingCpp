#include <iostream>
#include <random>

#include "analysis.h"
#include "input.h"

void random_experiment()
{
    std::random_device rd{};
    std::default_random_engine generator(rd());
    std::uniform_int_distribution distribution{1, 6};
    const int roll = distribution(generator);
    std::cout << "Dice roll " << roll << '\n';
}

void trading_game()
{
    const double start_price = 100.0; //<1>
    std::cout << "Stock bought for: " << start_price << '\n'; //<1>
    auto prices = stock_prices::get_prices(start_price, 10); //<2>
    for(auto price : prices) //<3>
    {
        std::cout << "Current price: " << price << '\n';
        std::cout << "Press (s) to sell\n>";
        char choice{};  //<4>
        std::cin >> choice; //<5>
        if (choice == 's') //<6>
        {
            const double profit = price - start_price; //<7>
            std::cout << "Profit " << profit << '\n';  //<7>
            break; //<8>
        }
    }
    std::cout << "Game over\n"; //<9>
}

int main()
{
    random_experiment();
    stock_prices::test_input();
    const auto prices = stock_prices::get_prices(100.0, 10);
//    const auto prices = stock_prices::get_prices(100.0, 10, 0.05); // or uncomment to use the normal distribution
    std::cout << "Got prices:\n";
    for(auto price : prices)
    {
        std::cout << price << '\n';
    }
    const auto profit = stock_prices::profit_on_first_uptick(prices);
    std::cout << "Profit " << profit << '\n';
    trading_game();


    std::random_device rd{};
    std::default_random_engine gen{rd()};
    std::normal_distribution<> distrib;
    double price = 100.0;
    const double volatility = 0.05;
    auto next_price = [volatility, &price, &gen, &distrib]() 
    {
        double percent  = volatility * distrib(gen);
        price += price * percent;
        return price;
    };
    const auto more_prices = stock_prices::get_prices(100.0, 10, next_price);

    const double step = price/100;
    std::uniform_int_distribution<> uniform_distrib{-1, +1};
    auto next_uniform_price = [step, &price, &gen, &uniform_distrib]()
    {
        price += step*uniform_distrib(gen);
        return price;
    };
    const auto even_more_prices = stock_prices::get_prices(100.0, 10, next_uniform_price);
}

