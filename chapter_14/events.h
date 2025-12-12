#include <iostream>
#include <string>
#include <variant>

namespace stock_prices
{
    struct Nothing //<1>
    {
    };

    struct FixedFine //<2>
    {
        double fine{};
    };

    struct Gift //<3>
    {
        double gift{};
    };

    struct InterestPayment //<4>
    {
        double percent{};
    };

    using Event = std::variant<Nothing,
	 FixedFine,
	 Gift,
	 InterestPayment,
	 std::string>; //<5>
    
    struct EventVisitor
    {
        double & funds; //<1>
        void operator()(Nothing) {}; //<2>
        void operator()(const FixedFine & event) //<3>
        {
            std::cout << "Fixed fine " << event.fine << '\n'; //<3>
            funds -= event.fine; //<3>
        }
        void operator()(const Gift & event) //<4>
        {
            std::cout << "Gift " << event.gift << '\n'; //<4>
            funds += event.gift; //<4>
        }
        void operator()(const InterestPayment & event) //<5>
        {
            std::cout << "Interest payment " << event.percent << "%\n"; //<5>
            funds *= (1.0 + event.percent); //<5>
        }
        void operator()(const std::string & message) //<6>
        {
            std::cout << message << '\n'; //<6>
        }
    };
    Event generate_event();
}
