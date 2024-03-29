//
// Created by April on 8/25/2019.
//

#pragma once

#include <vector>
#include "point.hpp"

class Board;

enum class Team {
    White,
    Black
};

Team opposite_team(Team team);

class Piece {
public:
    explicit Piece(Team team);
    virtual ~Piece() = default;
    Team team() const;
    virtual std::vector<Point> moves(Point origin, Board const& board) const = 0;
    char symbol() const;

protected:
    virtual char letter() const = 0;
private:
    Team team_;
};

std::vector<Point> adjacents();
std::vector<Point> diagonals();
std::vector<Point> neighbors();

std::vector<Point> make_extended_points(Point origin, Team team, Board const& board, std::vector<Point> const& dirs);
std::vector<Point> make_offset_points(Point origin, Team team, Board const& board, std::vector<Point> const& offsets);

namespace Pieces {
    class Pawn : public Piece{
    public:
        using Piece::Piece;
        std::vector<Point> moves(Point origin, Board const& board) const override;
    protected:
        char letter() const override;
    };

    class King : public Piece{
    public:
        using Piece::Piece;
        std::vector<Point> moves(Point origin, Board const& board) const override;
    protected:
        char letter() const override;
    };

    class Queen : public Piece{
    public:
        using Piece::Piece;
        std::vector<Point> moves(Point origin, Board const& board) const override;
    protected:
        char letter() const override;
    };

    class Bishop : public Piece{
    public:
        using Piece::Piece;
        std::vector<Point> moves(Point origin, Board const& board) const override;
    protected:
        char letter() const override;
    };

    class Knight : public Piece{
    public:
        using Piece::Piece;
        std::vector<Point> moves(Point origin, Board const& board) const override;
    protected:
        char letter() const override;
    };

    class Rook : public Piece {
    public:
        using Piece::Piece;
        std::vector<Point> moves(Point origin, Board const& board) const override;
    protected:
        char letter() const override;
    };
}