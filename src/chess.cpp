#include "chess.hpp"
//
// Created by April on 9/3/2019.
//

#include <vector>
#include <algorithm>
#include <utility>

#include "chess.hpp"
#include "piece.hpp"

using namespace chess;

RuleException::RuleException(RuleException::Type type):
    std::runtime_error{"Chess Rule Exception"},
    type_{type}
{}

RuleException::Type RuleException::type() const {
    return type_;
}

Action::Action(Team team):
    team_(team)
{}

Team Action::team() const {
    return team_;
}

Chess::Chess() :
    board_{8, 8},
    cur_team_{Team::White}
{}

std::unique_ptr<Piece> Chess::make_move(Point from, Point onto) {
    if (!board_.in_bounds(from) || !board_[from] || board_[from]->team() != cur_team_) {
        throw RuleException(RuleException::Type::NoPiece);
    }
    std::vector<Point> allowed_points = board_[from]->moves(from, board_);
    if (std::find(allowed_points.begin(), allowed_points.end(), onto) != allowed_points.end()) {
        std::unique_ptr<Piece> ret = std::move(board_[onto]);
        board_[onto] = std::move(board_[from]);
        return ret;
    } else {
        throw RuleException(RuleException::Type::IllegalMove);
    }
}

void Chess::change_team() {
    switch (cur_team_) {
    case Team::Black:
        cur_team_ = Team::White;
        break;
    case Team::White:
        cur_team_ = Team::Black;
        break;
    }
}

void action::Pass::handle(Chess& chess) const {
    chess.change_team();
}

void action::Move::handle(Chess &chess) const {
    chess.make_move(from_, onto_);
    chess.change_team();
}