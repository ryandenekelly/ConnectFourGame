#ifndef WIN_VALIDATOR_HPP
#define WIN_VALIDATOR_HPP

#include "Piece.hpp"
#include "Board.hpp"

class WinValidator
{
    public:
        WinValidator(Board * board);
        
        enum ValidatorStatus
        {
            NextCandidate,
            NextPiece,
            StreakNotFound,
            StreakFound
        };

        bool isGameOver(int streak_length=4);
        bool findStreak(int candidate_column, int top_of_column, int streak_length);

    private:
        Board * m_board;
        Piece::Type m_streakType;
        int m_streakCount;

        ValidatorStatus checkStreak(int x_pos, int y_pos, int streak_length);
        bool checkBoardFull();
        bool checkVertical(int streak_length);
        bool checkHorizontal(int streak_length);
        bool checkDiagonal(int streak_length);
        bool checkForwardDiagonal(int streak_length);
        bool checkBackwardsDiagonal(int streak_length);

        ValidatorStatus computeStreakIteration(int x_pos, int y_pos, int streak_length);
        bool checkTopLeft(int candidate_column, int top_of_column, int streak_length);
        bool checkLeft(int candidate_column, int top_of_column, int streak_length);
        bool checkBottomLeft(int candidate_column, int top_of_column, int streak_length);
        bool checkDown(int candidate_column, int top_of_column, int streak_length);
        bool checkBottomRight(int candidate_column, int top_of_column, int streak_length);
        bool checkRight(int candidate_column, int top_of_column, int streak_length);
        bool checkTopRight(int candidate_column, int top_of_column, int streak_length);

};
#endif