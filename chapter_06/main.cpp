#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

#include "analysis.h"
#include "input.h"

void first_main()
{
    std::vector prices{1.01, 2.02, 3.03, -4.04};
    auto lambda = [](double value){ return value < 0.0; };
//    bool invalid = lambda(-67.0); //unused, but shows how to call the lambda, just like a function
    auto erased = std::erase_if(prices, lambda);
    std::cout <<  erased << " prices below zero\n";
}

int main()
{
    stock_prices::test_input();

    std::cout << "Please enter some numbers.\n";
    auto prompt = [] () { std::cout << '>';};
    auto prices = stock_prices::get_prices(std::cin, prompt);
    std::cout << "Got " << prices.size() << " price(s) \n";

    std::cout <<"The following are valid:\n"; //<1>
    auto valid_prices = std::views::filter(prices, //<2>
		    [](double p) { return p >= 0.0; } ); //<3>
    for(double price : valid_prices) //<4>
    {
        std::cout << price << '\n';
    }
    const std::vector<double> valid_prices_as_vector =
	    std::ranges::to<std::vector>(valid_prices);
    const double mean = stock_prices::average(
		        valid_prices_as_vector
		    );
    std::cout << "with average " << mean << '\n';
    double potential_profit = 
	    stock_prices::profit_on_first_uptick(valid_prices_as_vector);
    std::cout << "Potential profit " << potential_profit << '\n';
    const double required_profit = 1.75;
    bool possible = 
        stock_prices::required_profit_possible(valid_prices_as_vector, required_profit);
    std::cout << "Required profit possible " << possible << '\n'; 
}
