//
// Created by April on 9/3/2019.
//

#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include "board.hpp"
#include "piece.hpp"

namespace chess {
    class RuleException : public std::runtime_error {
    public:
        enum class Type {
            NO_PIECE,
            ILLEGAL_MOVE
        };

        explicit RuleException(Type type);

        Type type() const;

    private:
        Type type_;
    };

    class Chess {
    public:
        Chess();

        std::unique_ptr<Piece> make_move(Point from, Point onto);

    private:
        Board board_;
        Team cur_team_;
    };
}

using chess::Chess;
