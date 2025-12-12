#include <iostream>
#include <string>
#include <variant>

namespace stock_prices
{
    struct Nothing
    {
        bool operator==(const Nothing &) const = default; //<1>
    };

    struct FixedFine
    {
        double fine{};
	bool operator==(const FixedFine &) const = default;//<2>
    };

    struct Gift
    {
        double gift{};
	bool operator==(const Gift &) const = default;//<3>
    };

    struct InterestPayment //<4>
    {
        double percent{};
	bool operator==(const InterestPayment &) const = default;//<4>
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

    struct DisplayEventName
    {
        void operator()(const Nothing &) //<1>
       	{
            std::cout << "Nothing";//<1>
	}; 
        void operator()(const FixedFine & event) //<2>
        {
            std::cout << "Fixed fine " << event.fine; //<2>
        }
        void operator()(const Gift & event) //<3>
        {
            std::cout << "Gift " << event.gift; //<3>
        }
        void operator()(const InterestPayment & event) //<4>
        {
            std::cout << "Interest payment " << event.percent << "%"; //<4>
        }
        void operator()(const std::string & message) //<5>
        {
            std::cout << message; //<5>
        }
    };
}

namespace std {
    using namespace stock_prices;
    template<> struct hash<Nothing> {
        size_t operator()(Nothing const&) const noexcept { return 0; }
    };
    template<> struct hash<FixedFine> {
        size_t operator()(FixedFine const& f) const noexcept {
            return std::hash<double>{}(f.fine);
        }
    };
    template<> struct hash<Gift> {
        size_t operator()(Gift const& g) const noexcept {
            return std::hash<double>{}(g.gift);
        }
    };
    template<> struct hash<InterestPayment> {
        size_t operator()(InterestPayment const& i) const noexcept {
            return std::hash<double>{}(i.percent);
        }
    };
}
