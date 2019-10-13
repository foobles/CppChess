#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <regex>
#include <memory>

#include "piece.hpp"
#include "chess.hpp"
#include "point.hpp"

class ParseInputError : public std::runtime_error {
public:
    ParseInputError():
        std::runtime_error("Error occurred parsing input.")
    {}
};

Point string_to_point(std::string const& str) {
    return {
        std::toupper(str[0]) - 'A',
        7 - (str[1] - '1')
    };
}

std::unique_ptr<chess::Input> get_input(Team cur_team) {
    std::string str;
    while (str.empty()) {
        std::getline(std::cin, str);
    }
    std::smatch sm;
    std::regex rg_move(R"(^\s*([A-Ha-h][1-8])\s+to\s+([A-Ha-h][1-8])\s*$)");
    std::regex rg_pass(R"(^\s*pass\s*$)");
    if (std::regex_search(str, sm, rg_move)) {
        return std::make_unique<chess::input::Move>(
                cur_team,
                string_to_point(sm[1].str()),
                string_to_point(sm[2].str()));
    } else if (std::regex_match(str, rg_pass)) {
        return std::make_unique<chess::input::Pass>(cur_team);
    } else {
        throw ParseInputError();
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}