#include <iostream>

#include "stock.h"

int main()
{
    stock_prices::Stock coffee{"Coffee", 4.8, 11.3}; //<1>
    std::cout << coffee.name  //<2>
	      << ", price " << coffee.last_price //<2>
	      << ", volatility " << coffee.volatility << '\n'; //<2>
    coffee.last_price = -12.34; //<3>
    std::cout << coffee.name  //<4>
	      << ", price " << coffee.last_price //<4>
	      << ", volatility " << coffee.volatility << '\n'; //<4>
}
