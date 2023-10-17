#include "WinValidator.hpp"
#include <iostream>

WinValidator::WinValidator(Board * board, Piece::Type streakType)
{
    m_board = board;
    m_streakCount = 0;
    m_streakType = Piece::Empty;
}

bool WinValidator::isGameOver()
{
    return checkVertical();
}

WinValidator::ValidatorStatus WinValidator::checkStreak(int x_pos, int y_pos)
{
    Piece currentPiece = m_board->getPiece(x_pos, y_pos);
    // if you reach an empty piece, that means no streak; Move to the next column.
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
    if(m_streakCount>=4)
    {
        return StreakFound;
    }
    return StreakNotFound;
}

bool WinValidator::checkBoardFull()
{
    return false;
}

bool WinValidator::checkVertical()
{
    // Go along the width of the board.
    for(int x_pos = 0; x_pos < m_board->getWidth(); x_pos++)
    {
        for(int y_pos=0; y_pos < m_board->getHeight(); y_pos++)
        {
            ValidatorStatus status = checkStreak(x_pos, y_pos);
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

bool WinValidator::checkHorizontal()
{
    return false;
}

bool WinValidator::checkDiagonal()
{
    return false;
}


