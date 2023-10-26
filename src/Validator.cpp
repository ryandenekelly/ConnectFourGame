#include "Validator.hpp"

#include <iostream>

Validator::Validator(Board * board)
{
    m_board = board;
    m_streakCount = 0;
    m_streakType = Piece::Empty;
}

/** @brief Function for the iterative step of finding a streak.
 * 
 *  @param x_pos The x-position for the current position in the search.
 *  @param y_pos The y-position for the current position in the search.
 *  @param streak_length The length of consecutive tokens to search for
 * 
 *  @return The status of the search as ValidatorStatus, 
 *  which determines if the search contniues or not in the function this was called from.
*/
Validator::ValidatorStatus Validator::computeStreakIteration(int x_pos, int y_pos, int streak_length)
{
    Piece currentPiece = m_board->getPiece(x_pos, y_pos);
    // if you reach an empty piece, that means no streak; Move to the next column.
    if(m_streakCount>=streak_length)
    {
        return StreakFound;
    }
    if(currentPiece.getType() == Piece::Empty)
    {
        return StreakNotFound;
    }
    // if steakType is still empty, a streak has not been started - so we start it.
    if(m_streakType == Piece::Empty)
    {
        m_streakType = currentPiece.getType();
        m_streakCount++;
        return NextPiece;
    }    
    // if the current streakType is the same as the current type, then increment the streak type
    if(m_streakType == currentPiece.getType())
    {
        m_streakCount++;
        return NextPiece;
    }
    // else the streak has ended
    else
    {
        return StreakNotFound;
    }

}

/** @brief check if the two opposite streaks will combine to make a streak greater than left streak.
 * 
 *  @param streaks vector of streak pairs (type and count).
 *  @param leftStreak left streak pair.
 *  @param rightStreak right streak pair.
 * 
 */
inline void Validator::checkOpposite(std::vector<std::pair<Piece::Type, int>>& streaks, std::pair<Piece::Type,
    int>& leftStreak, std::pair<Piece::Type, int>& rightStreak)
{   
    if(leftStreak.first != rightStreak.first)
    {
        streaks.emplace_back(leftStreak);
        streaks.emplace_back(rightStreak);
        return;
    }
    leftStreak.second = rightStreak.second + leftStreak.second;

    streaks.emplace_back(leftStreak);
    streaks.emplace_back(rightStreak);
}
std::vector<std::pair<Piece::Type, int>> Validator::findStreaks(int candidate_column, int top_of_column, int streak_length)
{
    std::vector<std::pair<Piece::Type, int>> streaks = {};

    std::pair<Piece::Type, int> rightStreak;
    std::pair<Piece::Type, int> leftStreak;

    // Baclwards Diagonal
    checkTopLeft(candidate_column-1, top_of_column+1, streak_length);
    leftStreak = std::make_pair(m_streakType, m_streakCount);

    checkBottomRight(candidate_column+1, top_of_column-1, streak_length);
    rightStreak = std::make_pair(m_streakType, m_streakCount);
    checkOpposite(streaks, leftStreak, rightStreak);

    // forwards diagonal
    checkTopRight(candidate_column+1, top_of_column+1, streak_length);
    leftStreak = std::make_pair(m_streakType, m_streakCount);

    checkBottomLeft(candidate_column-1, top_of_column-1, streak_length);
    rightStreak = std::make_pair(m_streakType, m_streakCount);
    checkOpposite(streaks, leftStreak, rightStreak);

    // Horizontal
    checkLeft(candidate_column-1, top_of_column, streak_length);
    leftStreak = std::make_pair(m_streakType, m_streakCount);
    
    checkRight(candidate_column+1, top_of_column, streak_length);
    rightStreak = std::make_pair(m_streakType, m_streakCount);
    checkOpposite(streaks, leftStreak, rightStreak);

    // Vertical
    checkDown(candidate_column, top_of_column-1, streak_length);
    streaks.emplace_back(std::make_pair(m_streakType, m_streakCount));


    return streaks;
}

bool Validator::checkTopLeft(int candidate_column, int top_of_column, int streak_length)
{
    
    m_streakType = Piece::Empty;
    m_streakCount = 0;

    int h = m_board->getHeight();
    int w = m_board->getHeight();


    for(int x_pos=candidate_column, y_pos=top_of_column; x_pos>=0 && y_pos<=h; x_pos--, y_pos++)
    {
            ValidatorStatus status = computeStreakIteration(x_pos, y_pos, streak_length);
            if(status == StreakNotFound)
            {
                break;
            }
            else if (status == StreakFound)
            {
                return m_streakType;
            }
    }
    return Piece::Empty;
}

bool Validator::checkLeft(int candidate_column, int top_of_column, int streak_length)
{
    m_streakType = Piece::Empty;
    m_streakCount = 0;
    
    int h = m_board->getHeight();
    int w = m_board->getHeight();


    for(int x_pos=candidate_column; x_pos>=0; x_pos--)
    {
            ValidatorStatus status = computeStreakIteration(x_pos, top_of_column, streak_length);
            if(status == StreakNotFound)
            {
                break;
            }
            else if (status == StreakFound)
            {
                return true;
            }
    }
    return false;
}

bool Validator::checkBottomLeft(int candidate_column, int top_of_column, int streak_length)
{
    m_streakType = Piece::Empty;
    m_streakCount = 0;
    int w = m_board->getWidth() - 1;
    int h = m_board->getHeight() - 1;

    for(int x_pos=candidate_column, y_pos=top_of_column; x_pos<w && y_pos>=0; x_pos++, y_pos--)
    {
            ValidatorStatus status = computeStreakIteration(x_pos, y_pos, streak_length);
            if(status == StreakNotFound)
            {
                break;
            }
            else if (status == StreakFound)
            {
                return true;
            }
    }
    return false;
}

bool Validator::checkDown(int candidate_column, int top_of_column, int streak_length)
{
    m_streakType = Piece::Empty;
    m_streakCount = 0;
    int w = m_board->getWidth() - 1;
    int h = m_board->getHeight() - 1;

    for(int y_pos=top_of_column; y_pos>=0; y_pos--)
    {
            ValidatorStatus status = computeStreakIteration(candidate_column, y_pos, streak_length);
            if(status == StreakNotFound)
            {
                break;
            }
            else if (status == StreakFound)
            {
                return true;
            }
    }
    return false;
}

bool Validator::checkBottomRight(int candidate_column, int top_of_column, int streak_length)
{
    m_streakType = Piece::Empty;
    m_streakCount = 0;
    int w = m_board->getWidth() - 1;
    int h = m_board->getHeight() - 1;

    for(int x_pos = candidate_column, y_pos=top_of_column; x_pos<w && y_pos>=0; x_pos++, y_pos--)
    {
            ValidatorStatus status = computeStreakIteration(x_pos, y_pos, streak_length);
            if(status == StreakNotFound)
            {
                break;
            }
            else if (status == StreakFound)
            {
                return true;
            }
            else // NextPiece and StreakNotFound.
            {
                continue;
            }
    }
    return false;
}

bool Validator::checkRight(int candidate_column, int top_of_column, int streak_length)
{
    m_streakType = Piece::Empty;
    m_streakCount = 0;
    int w = m_board->getWidth() - 1;
    int h = m_board->getHeight() - 1;

    for(int x_pos = candidate_column; x_pos<w ; x_pos++)
    {
            ValidatorStatus status = computeStreakIteration(x_pos, top_of_column, streak_length);
            if(status == StreakNotFound)
            {
                break;
            }
            else if (status == StreakFound)
            {
                return true;
            }

    }
    return false;

}

bool Validator::checkTopRight(int candidate_column, int top_of_column, int streak_length)
{
    m_streakType = Piece::Empty;
    m_streakCount = 0;
    int w = m_board->getWidth() - 1;
    int h = m_board->getHeight() - 1;

    for(int x_pos = candidate_column, y_pos = top_of_column; x_pos<w && y_pos<h; x_pos++, y_pos++)
    {
            ValidatorStatus status = computeStreakIteration(x_pos, y_pos, streak_length);
            if(status == StreakNotFound)
            {
                break;
            }
            else if (status == StreakFound)
            {
                return true;
            }
    }
    return false;
}