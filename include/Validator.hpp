#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include "Piece.hpp"
#include "Board.hpp"
#include <vector>

class Validator
{
    public:
        Validator(Board * board);
        
        enum ValidatorStatus
        {
            NextPiece,
            StreakNotFound,
            StreakFound
        };

        std::vector<std::pair<Piece::Type, int>> findStreaks(int candidate_column, int top_of_column, int streak_length);

    private:
        Piece::Type m_pieceType;
        Board * m_board;
        Piece::Type m_streakType;
        int m_streakCount;

        inline void checkOpposite(std::vector<std::pair<Piece::Type, int>>& streaks, std::pair<Piece::Type,
            int>& leftStreak, std::pair<Piece::Type, int>& rightStreak);

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