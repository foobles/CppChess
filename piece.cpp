//
// Created by Brad on 8/25/2019.
//

#include "piece.hpp"
#include "board.hpp"

Piece::Piece(Team team)
        : team_(team) {}

Team Piece::team() const {
    return team_;
}


std::vector<Point> adjacents() {
    return {{0,  -1},
            {1,  0},
            {0,  1},
            {-1, 0}};
}

std::vector<Point> diagonals() {
    return {{1,  1},
            {1,  -1},
            {-1, 1},
            {-1, -1}};
}

std::vector<Point> neighbors() {
    std::vector<Point> ret = adjacents();
    std::vector<Point> diags = diagonals();
    ret.insert(ret.end(), diags.begin(), diags.end());
    return ret;
}


std::vector<Point> make_extended_points(Point origin, Team team, Board const& board, std::vector<Point> const& dirs) {
    std::vector<Point> ret = {};
    for (Point offset : dirs) {
        Point cur = origin + offset;
        while (board.in_bounds(cur)) {
            if (board[cur]) {
                if (board[cur]->team() != team) {
                    ret.push_back(cur);
                }
                break;
            }
            ret.push_back(cur);
        }
    }
    return ret;
}

std::vector<Point> make_offset_points(Point origin, Team team, Board const& board, std::vector<Point> const &offsets) {
    std::vector<Point> ret = {};
    for (Point offset : offsets) {
        Point cur = origin + offset;
        if (board.in_bounds(cur)) {
            if (!board[cur] || board[cur]->team() != team) {
                ret.push_back(cur);
            }
        }
    }
    return ret;
}


using namespace Pieces;

Pawn::Pawn(Team team) :
    Piece(team)
{}


static int team_pawn_row(Team team) {
    switch (team) {
        case Team::Black:
            return 1;
        case Team::White:
            return 6;
    }
}

static Point team_dir(Team team) {
    switch (team) {
        case Team::Black:
            return {0, 1};
        case Team::White:
            return {0, -1};
    }
}

std::vector<Point> Pawn::moves(Point origin, Board const &board) const {
    Point forward = team_dir(team());
    std::vector<Point> offsets = {forward};
    if (origin.y == team_pawn_row(team())) {
        offsets.push_back(forward * 2);
    }
    Point diag_left = forward + Point{-1, 0};
    Point diag_right = forward + Point{1, 0};
    if (board.in_bounds(origin + diag_left) && board[origin + diag_left]) {
        offsets.push_back(diag_left);
    }
    if (board.in_bounds(origin + diag_right) && board[origin + diag_right]) {
        offsets.push_back(diag_right);
    }
    return offsets;
}

King::King(Team team) :
    Piece(team)
{}

std::vector<Point> King::moves(Point origin, Board const &board) const {
    return make_offset_points(origin, team(), board, neighbors());
}

Queen::Queen(Team team) :
    Piece(team)
{}

std::vector<Point> Queen::moves(Point origin, Board const &board) const {
    return make_extended_points(origin, team(), board, neighbors());
}

Bishop::Bishop(Team team) :
    Piece(team)
{}

std::vector<Point> Bishop::moves(Point origin, Board const &board) const {
    return make_extended_points(origin, team(), board, diagonals());
}

Knight::Knight(Team team) :
    Piece(team)
{}

std::vector<Point> Knight::moves(Point origin, Board const &board) const {
    return make_offset_points(origin, team(), board, {
            { 1, -2},
            { 2, -1},
            { 2,  1},
            { 1,  2},
            {-1,  2},
            {-2,  1},
            {-2, -1},
            {-1, -2}
    });
}

Rook::Rook(Team team) :
    Piece(team)
{}

std::vector<Point> Rook::moves(Point origin, Board const &board) const {
    return make_extended_points(origin, team(), board, adjacents());
}