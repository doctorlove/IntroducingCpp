#include <cassert> //<1>
#include <limits>
#include <sstream> //<2>

#include "input.h"

namespace stock_prices
{
    std::expected<double, std::string> get_number(std::istream & input_stream)
    {
        double number{};
        input_stream >> number;
        if(input_stream)
        {
            return number;
        }
        input_stream.clear(); 
        input_stream.ignore( 
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
        return std::unexpected{"That's not a number"};
    }

    // As before //<3>
    void test_input() //<4>
    {
	std::stringstream no_input{""}; //<5>
	auto no_op = [](){}; //<6>
        assert(get_prices(no_input, no_op).empty()); //<7>

	std::stringstream some_input{"1"}; //<8>
        assert(get_prices(some_input, no_op).size() == 1); //<9>
    }
}



