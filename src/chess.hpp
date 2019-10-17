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
    private:
        Board board_;
        Team cur_team_;
    };
}

using chess::Chess;
