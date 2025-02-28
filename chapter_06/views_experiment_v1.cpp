#include <iostream>
#include <ranges>
#include <vector>

int main()
{
    const std::vector prices{3.76, 1.5, -1.0, 3.0, 4.0, -2.0, 99.4}; //<1>
    const double required_price = 4.75; //<2>
    auto non_negative = [](double price) { return price >= 0.0; }; //<3>
    auto too_cheap = [required_price](double x) 
                     {
                         return x <= required_price; 
                     }; //<4>
    auto valid_prices = std::views::filter(prices,  non_negative); //<5>
    auto no_good = std::views::take_while(valid_prices, too_cheap); //<6>
    std::cout << "Too cheap:\n"; //<7>
    for(double p : no_good) //<7>
    {
        std::cout << p << '\n';
    }
    std::cout << "All prices:\n"; //<8>
    for(double p : valid_prices) //<8>
    {
        std::cout << p << '\n';
    }
}
