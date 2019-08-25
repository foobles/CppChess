//
// Created by Brad on 8/25/2019.
//

#include "piece.hpp"

Piece::Piece(Team team)
    : team_(team)
{}

Team Piece::team() const {
    return team_;
}