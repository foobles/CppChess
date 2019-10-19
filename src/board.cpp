//
// Created by April on 8/25/2019.
//

#include <cassert>
#include <utility>
#include <iostream>

#include "board.hpp"

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

static void draw_row_separator(int spaces) {
    for (int i = 0; i < spaces; ++i) {
        std::cout << "+--";
    }
    std::cout << "+\n";
}


void Board::draw(Team team) const {
    switch (team) {
    case Team::White:
        std::cout << "    ";
        for (int i = 1; i <= width_; ++i) {
            std::cout << i << "  ";
        }
        std::cout << '\n';

        for (int y = 0; y < height_; ++y) {
            std::cout << (height_ - y + 'A') << ' ';
            for (int x = 0; x < width_; ++x) {
                PiecePtr const& cur_piece = (*this)[{x, y}];
                std::cout << "| " << (cur_piece? cur_piece->symbol() : ' ');
            }
            std::cout << "|\n";
            draw_row_separator(width_);
        }
        draw_row_separator(width_);
        break;
    case Team::Black:
            std::cout << "    ";
            for (int i = width_; i >= 1; --i) {
                std::cout << i << "  ";
            }
            std::cout << '\n';

            for (int y = height_ - 1; y >= 0; --y) {
                std::cout << (height_ - y + 'A') << ' ';
                for (int x = width_ - 1; x >= 0; --x) {
                    PiecePtr const& cur_piece = (*this)[{x, y}];
                    std::cout << "| " << (cur_piece? cur_piece->symbol() : ' ');
                }
                std::cout << "|\n";
                draw_row_separator(width_);
            }
            draw_row_separator(width_);
            break;
    }
}