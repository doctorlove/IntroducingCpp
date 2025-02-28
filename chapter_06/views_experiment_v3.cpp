#include <iostream>
#include <ranges>
#include <vector>

int main()
{
    const std::vector prices{3.76, 1.5, -1.0, 3.0, 4.0, -2.0, 99.4};
    const double required_price = 4.75;
    auto non_negative = [](double price) { return price >= 0.0; };
    auto too_cheap = [required_price](double x) 
    { 
        std::cout << "Comparing " << x << '\n'; //<1>
        return x <= required_price; 
    };
    auto no_good = prices | std::views::filter(non_negative)
                          | std::views::take_while(too_cheap); //<2>
    std::cout << "Too cheap:\n";  //<3>
    for(double p : no_good) //<4>
    {
        std::cout << p << '\n';
    }
}
