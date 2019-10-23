//
// Created by April on 8/25/2019.
//

#include <cctype>
#include "piece.hpp"
#include "board.hpp"

Team opposite_team(Team team) {
    switch (team) {
    case Team::Black:
        return Team::White;
    case Team::White:
        return Team::Black;
    }
    return static_cast<Team>(-1);
}

Piece::Piece(Team team)
        : team_(team) {}

Team Piece::team() const {
    return team_;
}

char Piece::symbol() const {
    switch (team_) {
        case Team::Black:
            return std::toupper(letter());
        case Team::White:
            return std::tolower(letter());
    }
    return -1;
}

std::vector<Point> adjacents() {
    return {{ 0, -1},
            { 1,  0},
            { 0,  1},
            {-1,  0}};
}

std::vector<Point> diagonals() {
    return {{ 1,  1},
            { 1, -1},
            {-1,  1},
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
            cur += offset;
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

static int team_pawn_row(Team team) {
    switch (team) {
        case Team::Black:
            return 1;
        case Team::White:
            return 6;
    }
    return -1;
}

static Point team_dir(Team team) {
    switch (team) {
        case Team::Black:
            return {0, 1};
        case Team::White:
            return {0, -1};
    }
    return {-1, -1};
}

std::vector<Point> Pawn::moves(Point origin, Board const &board) const {
    Point forward = team_dir(team());
    std::vector<Point> offsets = {};
    if (!board[origin + forward]) {
        offsets.push_back(forward);
    }
    if (origin.y == team_pawn_row(team()) && !board[origin + forward * 2]) {
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
    return make_offset_points(origin, team(), board, offsets);
}

char Pawn::letter() const {
    return 'p';
}

std::vector<Point> King::moves(Point origin, Board const &board) const {
    return make_offset_points(origin, team(), board, neighbors());
}

char King::letter() const {
    return 'k';
}

std::vector<Point> Queen::moves(Point origin, Board const &board) const {
    return make_extended_points(origin, team(), board, neighbors());
}

char Queen::letter() const {
    return 'q';
}

std::vector<Point> Bishop::moves(Point origin, Board const &board) const {
    return make_extended_points(origin, team(), board, diagonals());
}

char Bishop::letter() const {
    return 'b';
}

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

char Knight::letter() const {
    return 'n';
}

std::vector<Point> Rook::moves(Point origin, Board const &board) const {
    return make_extended_points(origin, team(), board, adjacents());
}

char Rook::letter() const {
    return 'r';
}