#include <iostream>
#include <string>
#include <vector>
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

std::string team_as_string(Team t) {
    switch (t) {
    case Team::White:
        return "White";
    case Team::Black:
        return "Black";
    }
    return "";
}

int main() {
    Chess chess_game;
    std::string message;

    while (true) {
        chess_game.board().draw(chess_game.cur_team());
        std::cout << message;
        message.clear();
        std::string cur_team_str = team_as_string(chess_game.cur_team());
        if (chess_game.is_in_check(chess_game.cur_team())) {
            if (chess_game.is_in_checkmate(chess_game.cur_team())) {
                std::cout << cur_team_str << "is in checkmate. Game Over!\n";
                break;
            }
            std::cout << cur_team_str << " is in check.\n";
        }
        std::cout << "It is " << cur_team_str << "'s turn.\n";
        try {
            get_input(chess_game.cur_team(), &chess_game)->handle(chess_game);
        } catch (ParseInputError const& e) {
            message = "Bad input.\n";
        } catch (chess::RuleException const& e) {
            switch (e.type()) {
            case chess::RuleException::Type::IllegalMove:
                message = "You aren't allowed to move that there.\n";
                break;
            case chess::RuleException::Type::NoPiece:
                message = "You have no piece there.\n";
                break;
            case chess::RuleException::Type::WrongTeam:
                message = "You can only move your own pieces.\n";
                break;
            case chess::RuleException::Type::MoveIntoCheck:
                message = "You cannot move into check.\n";
                break;
            }
        }

    }

    return 0;
}