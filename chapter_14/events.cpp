#include <array>
#include <random>

#include "events.h"

stock_prices::Event stock_prices::generate_event()
{
    static std::mt19937 engine{ std::random_device{}() };//<1>
    std::array<Event, 5> events{ Nothing{},
        FixedFine{2.5},
        Gift{25.00},
        InterestPayment{0.04},
        "You won a free magazine"};//<2>
    std::discrete_distribution<> dist({ 60, 10, 10, 10, 10 });//<3>

    return events[dist(engine)];//<4>
}
