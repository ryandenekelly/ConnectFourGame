#include "WinValidator.hpp"
#include <iostream>
#include <vector>

#define BUILD_LOOP(TYPE) ()
#define TOP_LEFT(X,Y,H) ({for(int x_pos=X, y_pos=Y; x_pos>=0 && y_pos<=H; x_pos--, y_pos++)})

WinValidator::WinValidator(Board * board)
{
    m_board = board;
    m_streakCount = 0;
    m_streakType = Piece::Empty;
}


bool WinValidator::isGameOver(int streak_length)
{
    if(checkBoardFull())
    {
        return true;
    }
    if(checkVertical(streak_length))
    {
        return true;
    }
    if(checkHorizontal(streak_length))
    {
        return true;
    }
    if(checkForwardDiagonal(streak_length))
    {
        return true;
    }
    if(checkBackwardsDiagonal(streak_length))
    {
        return true;
    }
    return false;
}

WinValidator::ValidatorStatus WinValidator::checkStreak(int x_pos, int y_pos, int streak_length)
{
    Piece currentPiece = m_board->getPiece(x_pos, y_pos);
    // if you reach an empty piece, that means no streak; Move to the next column. TODO: Fix me - this doesn't apply to diagonals!
    if(currentPiece.getType() == Piece::Empty)
    {
        return NextCandidate;
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
    }
    // else it is not the same, so switch the type and reset the streak.
    else
    {
        m_streakType = currentPiece.getType();
        m_streakCount = 1;
        return NextPiece;
    }
    if(m_streakCount>=streak_length)
    {
        return StreakFound;
    }
    return StreakNotFound;
}

bool WinValidator::checkBoardFull()
{
    int w = m_board->getWidth();
    for(int x_pos = 0; x_pos < w; x_pos++)
    {
        if(m_board->getPiece(x_pos, m_board->getHeight()-1).getType() != Piece::Empty)
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool WinValidator::checkVertical(int streak_length)
{
    // Go along the width of the board.
    for(int x_pos = 0; x_pos < m_board->getWidth(); x_pos++)
    {
        m_streakType = Piece::Empty;
        m_streakCount = 0;
        for(int y_pos=0; y_pos < m_board->getHeight(); y_pos++)
        {
            ValidatorStatus status = checkStreak(x_pos, y_pos, streak_length);
            if(status == NextCandidate)
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
    }
    return false;
}

bool WinValidator::checkHorizontal(int streak_length)
{
    // go up the column.
    for(int y_pos=0; y_pos < m_board->getHeight(); y_pos++)
    {
        m_streakType = Piece::Empty;
        m_streakCount = 0;
        for(int x_pos=0; x_pos < m_board->getWidth(); x_pos++)
        {
            ValidatorStatus status = checkStreak(x_pos, y_pos, streak_length);
            if(status == NextCandidate)
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
    }
    return false;
}

bool WinValidator::checkForwardDiagonal(int streak_length)
{
    int h = m_board->getHeight();
    int w = m_board->getWidth();

    // valid streak origins from left side
    for(int origin_x = 0, origin_y = h-4; origin_x>=0 && origin_y>= 0; origin_y--)
    {
        m_streakType = Piece::Empty;
        m_streakCount = 0;
        for(int streak_x = origin_x, streak_y = origin_y; streak_x<w && streak_y<h; streak_x++, streak_y++)
        {
            // TODO: comparison here
            ValidatorStatus status = checkStreak(streak_x, streak_y, streak_length);
            // For diagonals we can't early exit here.
            if (status == StreakFound)
            {
                return true;
            }
            else // NextPiece and StreakNotFound.
            {
                continue;
            }
        }
    }

    // valid streak origins from bottom side
    for(int origin_x = 1, origin_y = 0; origin_x<w-4 && origin_y>= 0; origin_x++)
    {
        m_streakType = Piece::Empty;
        m_streakCount = 0;

        for(int streak_x = origin_x, streak_y = origin_y; streak_x<w && streak_y<h; streak_x++, streak_y++)
        {
            // TODO: comparison here
            ValidatorStatus status = checkStreak(streak_x, streak_y, streak_length);
            // For diagonals we can't early exit here.
            if (status == StreakFound)
            {
                return true;
            }
            else // NextPiece and StreakNotFound.
            {
                continue;
            }
        }
    }
    return false;
}

bool WinValidator::checkBackwardsDiagonal(int streak_length)
{
    int h = m_board->getHeight();
    int w = m_board->getWidth();
    int midpoint = w/2;

    // valid streak origins from right side
    for(int origin_x = w-1, origin_y = h-4; origin_x>=midpoint && origin_y>= 0; origin_y--)
    {
        m_streakType = Piece::Empty;
        m_streakCount = 0;
        for(int streak_x = origin_x, streak_y = origin_y; streak_x>=0 && streak_y<h; streak_x--, streak_y++)
        {
            // TODO: comparison here           
            ValidatorStatus status = checkStreak(streak_x, streak_y, streak_length);
            // For diagonals we can't early exit here.
            if (status == StreakFound)
            {
                return true;
            }
            else // NextPiece and StreakNotFound.
            {
                continue;
            }
        }
    }

    // valid streak origins from bottom side
    for(int origin_x = w-1, origin_y = 0; origin_x>=midpoint && origin_y>= 0; origin_x--)
    {
        m_streakType = Piece::Empty;
        m_streakCount = 0;

        for(int streak_x = origin_x, streak_y = origin_y; streak_x>=0 && streak_y<h; streak_x--, streak_y++)
        {
            // TODO: comparison here            
            ValidatorStatus status = checkStreak(streak_x, streak_y, streak_length);
            // For diagonals we can't early exit here.
            if (status == StreakFound)
            {
                return true;
            }
            else // NextPiece and StreakNotFound.
            {
                continue;
            }
        }

    }
    return false;
}