//
// Created by April on 8/25/2019.
//

#pragma once

#include <memory>
#include <vector>

#include "point.hpp"

class Piece;

class Board {
public:
    using PiecePtr = std::unique_ptr<Piece>;

    Board(int width, int height);
    ~Board();

    Board(Board const&) = delete;

    int width() const;
    int height() const;

    PiecePtr const& operator[](Point point) const;
    PiecePtr& operator[](Point point);

    PiecePtr move_piece(Point from, Point onto);

    bool in_bounds(Point p) const;
private:
    int width_;
    int height_;
    std::vector<PiecePtr> data_;
};




