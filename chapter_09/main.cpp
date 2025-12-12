#include <print>
#include <iostream> // TODO remove

#include "analysis.h"
#include "input.h"

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

int main(int argc, char *argv[])
{
    const auto prices = stock_prices::get_prices(100.0, 10);
    for(auto price: prices)
    {
        std::println("{:.2f}", price);
    }
}
