#include <filesystem>
#include <fstream> //<1>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "input.h"

void write_to_file(const std::vector<double> & prices, 
		const std::string & filename)
{
    std::ofstream file{filename}; //<2>
    if(file) //<3>
    {
        for(auto price: prices) //<4>
        {
            file << price << '\n';  //<4>
        }
        std::cout <<"Wrote to prices.txt\n";
    }
    else
    {
        throw std::runtime_error("Failed to write to prices.txt");
    }
}

void write_to_file_improved(const std::vector<double> & prices,
	       const std::string & filename)
{
    const std::filesystem::path path = std::filesystem::current_path(); //<1>
    const auto fully_pathed_filename = path / filename; //<2>
    std::ofstream file{filename};
    if(file)
    {
        for(auto price: prices)
        {
            file << price << '\n';
        }
        std::cout <<"Wrote to " << fully_pathed_filename << '\n'; //<3>
    }
    else
    {
        auto error_message = "Failed to write to " + //<4>
		fully_pathed_filename.string(); //<5>
        throw std::runtime_error(error_message); //<6>
    }
}

int main()
{
    write_to_file(stock_prices::get_prices(100.0, 10, 0.05), "prices,txt"); //<5>
}
