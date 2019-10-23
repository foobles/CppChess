//
// Created by April on 8/25/2019.
//

#pragma once

#include <memory>
#include <vector>

#include "point.hpp"
#include "piece.hpp"

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

    void draw(Team team) const;

    using Iterator = std::vector<PiecePtr>::iterator;
    using ConstIterator = std::vector<PiecePtr>::const_iterator;

    Iterator begin();
    Iterator end();

    ConstIterator begin() const;
    ConstIterator end() const;

    std::vector<Point> points() const;

private:

    int width_;
    int height_;
    std::vector<PiecePtr> data_;
};




