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
            NoPiece,
            IllegalMove,
            MoveIntoCheck,
            WrongTeam
        };

        explicit RuleException(Type type);

        Type type() const;

    private:
        Type type_;
    };

    class Chess;

    namespace action {
        class Action {
        public:
            explicit Action(Team team);
            virtual ~Action() = default;
            virtual void handle(Chess&) const = 0;
            Team team() const;
        private:
            Team team_;
        };

        class Pass : public Action {
        public:
            using Action::Action;
            void handle(Chess& chess) const override;
        };

        class Move : public Action {
        public:
            Move(Team team, Point from, Point onto);
            void handle(Chess& chess) const override;
        private:
            Point from_;
            Point onto_;
        };
    }

    using action::Action;

    class Chess {
    public:
        Chess();

        std::unique_ptr<Piece> make_move(Point from, Point onto);

        void change_team();

        Team cur_team() const;

        Board const& board() const;
        Board& board();

        bool is_in_check(Team team) const;

        bool threatens_king(Point p, Team team) const;

        bool is_in_checkmate(Team team);

        std::unique_ptr<Piece> make_move_unchecked(Point from, Point onto);
    private:
        template <typename F>
        void with_simulated_move(Point from, Point onto, F func) {
            Team prev_team = cur_team_;
            cur_team_ = board_[from]->team();
            std::unique_ptr<Piece> taken = make_move_unchecked(from, onto);
            func(const_cast<Chess const&>(*this));
            board_.move_piece(onto, from);
            board_[onto] = std::move(taken);
            cur_team_ = prev_team;
        }

        Board board_;
        Team cur_team_;
    };
}

using chess::Chess;
