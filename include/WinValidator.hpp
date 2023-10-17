#ifndef WIN_VALIDATOR_HPP
#define WIN_VALIDATOR_HPP

#include "Piece.hpp"
#include "Board.hpp"

class WinValidator
{
    public:
        WinValidator(Board * board, Piece::Type streakType);
        
        enum ValidatorStatus
        {
            NextCandidate,
            NextPiece,
            StreakNotFound,
            StreakFound
        };

        bool isGameOver();

    private:
        Board * m_board;
        Piece::Type m_streakType;
        int m_streakCount;

        ValidatorStatus checkStreak(int x_pos, int y_pos);
        bool checkBoardFull();
        bool checkVertical();
        bool checkHorizontal();
        bool checkDiagonal();

};
#endif