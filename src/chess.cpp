#include "chess.hpp"
//
// Created by April on 9/3/2019.
//

#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_set>

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
{
    for (int i = 0; i < board_.width(); i++) {
        board_[{i, 1}] = std::make_unique<Pieces::Pawn>(Team::Black);
        board_[{i, 6}] = std::make_unique<Pieces::Pawn>(Team::White);
    }

    board_[{0, 0}] = std::make_unique<Pieces::Rook>(Team::Black);
    board_[{1, 0}] = std::make_unique<Pieces::Knight>(Team::Black);
    board_[{2, 0}] = std::make_unique<Pieces::Bishop>(Team::Black);
    board_[{3, 0}] = std::make_unique<Pieces::Queen>(Team::Black);
    board_[{4, 0}] = std::make_unique<Pieces::King>(Team::Black);
    board_[{5, 0}] = std::make_unique<Pieces::Bishop>(Team::Black);
    board_[{6, 0}] = std::make_unique<Pieces::Knight>(Team::Black);
    board_[{7, 0}] = std::make_unique<Pieces::Rook>(Team::Black);

    board_[{0, 7}] = std::make_unique<Pieces::Rook>(Team::White);
    board_[{1, 7}] = std::make_unique<Pieces::Knight>(Team::White);
    board_[{2, 7}] = std::make_unique<Pieces::Bishop>(Team::White);
    board_[{3, 7}] = std::make_unique<Pieces::Queen>(Team::White);
    board_[{4, 7}] = std::make_unique<Pieces::King>(Team::White);
    board_[{5, 7}] = std::make_unique<Pieces::Bishop>(Team::White);
    board_[{6, 7}] = std::make_unique<Pieces::Knight>(Team::White);
    board_[{7, 7}] = std::make_unique<Pieces::Rook>(Team::White);
}

std::unique_ptr<Piece> Chess::make_move(Point from, Point onto) {
    if (!board_.in_bounds(from) || !board_[from] || board_[from]->team() != cur_team_) {
        throw RuleException(RuleException::Type::NoPiece);
    }
    std::vector<Point> allowed_points = board_[from]->moves(from, board_);
    if (std::find(allowed_points.begin(), allowed_points.end(), onto) != allowed_points.end()) {
        std::unique_ptr<Piece> ret = make_move_unchecked(from, onto);
        if (is_in_check(cur_team_)) {
            board_[from] = std::move(board_[onto]);
            board_[onto] = std::move(ret);
            throw RuleException(RuleException::Type::MoveIntoCheck);
        }
        return ret;
    } else {
        throw RuleException(RuleException::Type::IllegalMove);
    }
}

void Chess::change_team() {
    cur_team_ = opposite_team(cur_team_);
}

Team Chess::cur_team() const {
    return cur_team_;
}

void action::Pass::handle(Chess& chess) const {
    chess.change_team();
}

action::Move::Move(Team team, Point from, Point onto):
    Action(team),
    from_(from),
    onto_(onto)
{}

void action::Move::handle(Chess &chess) const {
    chess.make_move(from_, onto_);
    chess.change_team();
}

Board& Chess::board() {
    return board_;
}

Board const& Chess::board() const {
    return board_;
}

bool Chess::is_in_check(Team team) const {
    for (Point p : board_.points()) {
        if (board_[p] &&
                board_[p]->team() == opposite_team(team) &&
                threatens_king(p, team))
        {
            return true;
        }
    }
    return false;
}

bool Chess::threatens_king(Point p, Team team) const {
    auto moves = board_[p]->moves(p, board_);
    for (Point move : moves) {
        std::unique_ptr<Piece> const& move_piece = board_[move];
        if (move_piece &&
                dynamic_cast<Pieces::King const*>(move_piece.get()) &&
                move_piece->team() == team)
        {
            return true;
        }
    }
    return false;
}

bool Chess::is_in_checkmate(Team team) {
    for (Point p : board_.points()) {
        if (board_[p] && board_[p]->team() == team) {
            for (Point move : board_[p]->moves(p, board_)) {
                bool in_check = false;
                with_simulated_move(p, move, [&in_check, team](Chess const &c) {
                    if (c.is_in_check(team)) {
                        in_check = true;
                    }
                });
                if (!in_check) {
                    return false;
                }
            }
        }
    }
    return true;
}

std::unique_ptr<Piece> Chess::make_move_unchecked(Point from, Point onto) {
    std::unique_ptr<Piece> ret = std::move(board_[onto]);
    board_[onto] = std::move(board_[from]);
    return ret;
}