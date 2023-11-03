#ifndef QUICK_VALIDATOR_HPP
#define QUICK_VALIDATOR_HPP

#include "Board.hpp"


class QuickValidator
{
    public:
        QuickValidator(Board * board);

        struct Streak
        {
            int count;
            Piece::Type type;
        };
        
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

        Streak isWinningMove(int x);
        Streak getStreak(int x_pos);
        inline int countLeft(int origin_x, int origin_y, Piece::Type currentPieceType);
        inline int countRight(int origin_x, int origin_y, Piece::Type currentPieceType);
        inline int countBackwardsDiagonalUp(int origin_x, int origin_y, Piece::Type currentPieceType);
        inline int countBackwardsDiagonalDown(int origin_x, int origin_y, Piece::Type currentPieceType);
        inline int countForwardsDiagonalUp(int origin_x, int origin_y, Piece::Type currentPieceType);
        inline int countForwardsDiagonalDown(int origin_x, int origin_y, Piece::Type currentPieceType);
        inline int countDown(int origin_x, int origin_y, Piece::Type currentPieceType);

    
    private:
        Board * m_board;

};

#endif