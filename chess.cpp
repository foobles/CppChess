#include "chess.hpp"
//
// Created by April on 9/3/2019.
//

#include <vector>
#include <algorithm>
#include <utility>

#include "chess.hpp"

using namespace chess;

RuleException::RuleException(RuleException::Type type):
    std::runtime_error{"Chess Rule Exception"},
    type_{type}
{}

RuleException::Type RuleException::type() const {
    return type_;
}

Chess::Chess() :
    board_{8, 8},
    cur_team_{Team::White}
{}

std::unique_ptr<Piece> Chess::make_move(Point from, Point onto) {
    if (!board_.in_bounds(from) || !board_[from] || board_[from]->team() != cur_team_) {
        throw RuleException(RuleException::Type::NO_PIECE);
    }
    std::vector<Point> allowed_points = board_[from]->moves(from, board_);
    if (std::find(allowed_points.begin(), allowed_points.end(), onto) != allowed_points.end()) {
        std::unique_ptr<Piece> ret = std::move(board_[onto]);
        board_[onto] = std::move(board_[from]);
        return ret;
    } else {
        throw RuleException(RuleException::Type::ILLEGAL_MOVE);
    }
}
