//
// Created by April on 9/3/2019.
//

#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include "board.hpp"
#include "piece.hpp"

class RuleException : public std::runtime_error {
public:
    enum class Type {
        NO_PIECE,
        ILLEGAL_MOVE
    };

    explicit RuleException(Type type, std::string&& message = "Cannot make move");

    Type type() const;

private:
    Type type_;
};

class Chess {
public:
    Chess();

    bool make_move(Point from, Point onto);

private:
    Board board_;
    Team cur_team_;
};




