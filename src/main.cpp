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

void print_point(Point p) {
    std::cout << '{' << p.x << ", " << p.y << '}';
}

std::unique_ptr<chess::Action> get_input(Team cur_team, Chess* ch = nullptr) {
    std::string str;
    while (str.empty()) {
        std::getline(std::cin, str);
    }
    std::smatch sm;
    std::regex rg_move(R"(^\s*([A-Ha-h][1-8])\s+to\s+([A-Ha-h][1-8])\s*$)");
    std::regex rg_pass(R"(^\s*pass\s*$)");
    std::regex rg_get_moves(R"(^get\s+([A-Ha-h][1-8])\s*$)");
    if (std::regex_search(str, sm, rg_move)) {
        return std::make_unique<chess::action::Move>(
                cur_team,
                string_to_point(sm[1].str()),
                string_to_point(sm[2].str()));
    } else if (std::regex_match(str, rg_pass)) {
        return std::make_unique<chess::action::Pass>(cur_team);
    }
    throw ParseInputError();

}

int main() {
    Chess chess_game;


    while (true) {
        chess_game.board().draw(chess_game.cur_team());
        try {
            get_input(chess_game.cur_team(), &chess_game)->handle(chess_game);
            if (([]{return false;})()) break;
        } catch (ParseInputError const& e) {
            std::cout << "Bad input.\n";
        } catch (chess::RuleException const& e) {
            switch (e.type()) {
            case chess::RuleException::Type::IllegalMove:
                std::cout << "You aren't allowed to move that there.\n";
                break;
            case chess::RuleException::Type::NoPiece:
                std::cout << "You have no piece there.\n";
                break;
            case chess::RuleException::Type::WrongTeam:
                std::cout << "You can only move your own pieces.\n";
                break;
            }
        }
    }

    return 0;
}