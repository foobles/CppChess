//
// Created by April on 9/3/2019.
//

#pragma once

#include "board.hpp"
#include "piece.hpp"

class Chess {
public:
    Chess();

    bool make_move(Point from, Point onto);

private:
    Board board_;
    Team cur_team_;
};




