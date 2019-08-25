//
// Created by Brad on 8/25/2019.
//

#pragma once

#include <vector>
#include "point.hpp"

class Board;

enum class Team {
    White,
    Black
};

class Piece {
public:
    Piece(Team team);
    Team team() const;

    virtual std::vector<Point> moves(Point origin, Board const& board) const = 0;
private:
    Team team_;
};