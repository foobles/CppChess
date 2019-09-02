//
// Created by Brad on 8/25/2019.
//

#include <cassert>
#include <utility>

#include "board.hpp"
#include "piece.hpp"


Board::Board(int width, int height) :
    width_(width),
    height_(height),
    data_(width * height)
{}

Board::~Board() = default;

int Board::width() const {
    return width_;
}

int Board::height() const {
    return height_;
}

Board::PiecePtr const& Board::operator[](Point point) const {
    return data_[point.idx(width_)];
}

Board::PiecePtr& Board::operator[](Point point) {
    return data_[point.idx(width_)];
}

Board::PiecePtr Board::move_piece(Point from, Point onto) {
    std::unique_ptr<Piece>& piece = (*this)[from];
    assert(piece);
    std::unique_ptr<Piece> ret = std::move((*this)[onto]);
    (*this)[onto] = std::move(piece);
    return ret;
}

bool Board::in_bounds(Point p) const {
    return p.x >= 0
        && p.x < width_
        && p.y >= 0
        && p.y < height_;
}

