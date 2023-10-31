#ifndef QUICK_VALIDATOR_HPP
#define QUICK_VALIDATOR_HPP

#include "Board.hpp"


class QuickValidator
{
    public:
        QuickValidator(Board * board);

        enum Direction
        {
            Left,
            Right,
            ForwardsUp,
            ForwardsDown,
            BackwardsUp,
            BackwardsDown,
            Down
        };

        bool isWinningMove();
        int getStreak(int x_pos);
        inline int countLeft(int origin_x, int origin_y, Piece::Type currentPieceType);
        inline int countRight(int origin_x, int origin_y, Piece::Type currentPieceType);
        inline int countBackwardsDiagonalUp(int origin_x, int origin_y, Piece::Type currentPieceType);
        inline int countBackwardsDiagonalDown(int origin_x, int origin_y, Piece::Type currentPieceType);
        inline int countForwardsDiagonalUp(int origin_x, int origin_y, Piece::Type currentPieceType);
        inline int countForwardsDiagonalDown(int origin_x, int origin_y, Piece::Type currentPieceType);
        inline int countDown(int origin_x, int origin_y, Piece::Type currentPieceType);

        inline int countGeneric(int origin_x, int origin_y, Piece::Type currentPieceType, Direction direction);
        int getStreakGeneric(int x_pos);
        int getExpressionX(int origin_x, int step, QuickValidator::Direction direction);
        int getExpressionY(int origin_y, int step, QuickValidator::Direction direction);
    
    private:
        Board * m_board;

};

#endif