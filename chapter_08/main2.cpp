#include <filesystem>
#include <fstream> //<1>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "input.h"

void write_to_file(const std::vector<double> & prices, 
		const std::string & filename) //<1>
{
    const std::filesystem::path path = std::filesystem::current_path(); //<2>
    const auto fully_pathed_filename = path / filename; //<3>
    std::ofstream file{filename};
    if(file)
    {
        for(auto price: prices)
        {
            file << price << '\n';
        }
        std::cout <<"Wrote to " << fully_pathed_filename << '\n'; //<4>
    }
    else
    {
        auto error_message = "Failed to write to " + //<5>
		fully_pathed_filename.string(); //<6>
        throw std::runtime_error(error_message); //<7>
    }
}

void read_from_file(const std::string & filename) //<1>
{
    std::ifstream file{filename}; //<2>
    if(file) //<3>
    {
        auto prices = stock_prices::get_prices(file, [](){}); //<4>
        for(auto price: prices) //<5>
        {
            std::cout << price << '\n'; //<5>
        }
    }
    else
    {
        throw std::runtime_error("Failed to read from file"); //<6>
    }
}

int main()
{
    try
    {
        write_to_file(stock_prices::get_prices(100.0, 10, 0.05), "prices.txt"); //<7>
        read_from_file("prices.txt"); //<8>
        return 0;
    }
    catch(const std::exception & e)
    {
        std::cout << e.what() << '\n';
	return -1;
    }
}
