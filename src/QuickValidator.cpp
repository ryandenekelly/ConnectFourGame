#include "QuickValidator.hpp"
#include <algorithm>
#include <iostream>

QuickValidator::QuickValidator(Board * board)
{
    m_board = board;
}

QuickValidator::Streak QuickValidator::isWinningMove(int x_pos)
{
    std::array<Streak,10> countArray = {};
    int y_pos = m_board->getTopOfColumns()[x_pos];
    y_pos = y_pos>0 ? y_pos-1 : y_pos;

    // Left
    Piece::Type leftType = m_board->getPiece(x_pos, y_pos).getType();
    countArray[0] = {countLeft(x_pos, y_pos, leftType), leftType};

    // Right
    Piece::Type rightType = m_board->getPiece(x_pos, y_pos).getType();
    countArray[1] = {countRight(x_pos, y_pos, rightType), rightType};

    // Left+Right
    // Have to account for (x_pos, y_pos) being counted twice!
    countArray[2] = (leftType != Piece::Empty) && (leftType == rightType) ? 
        (struct Streak){(countArray[0].count + countArray[1].count-1), leftType} 
            : (struct Streak){0, Piece::Empty};
    
    // Forwards Diagonal
    Piece::Type forwardsTypeUp = m_board->getPiece(x_pos, y_pos).getType();
    countArray[3] = {countForwardsDiagonalUp(x_pos, y_pos, forwardsTypeUp), forwardsTypeUp};

    Piece::Type forwardsTypeDown = m_board->getPiece(x_pos, y_pos).getType();
    countArray[4] = {countForwardsDiagonalDown(x_pos, y_pos, forwardsTypeDown), forwardsTypeDown};

    // Forwards up+down
    // Have to account for (x_pos, y_pos) being counted twice!
    countArray[5] = (forwardsTypeUp != Piece::Empty) && (forwardsTypeUp == forwardsTypeDown) ?
        (struct Streak){countArray[3].count + countArray[4].count-1, forwardsTypeUp} 
            : (struct Streak){0, Piece::Empty};

    // Backwards Digonal
    Piece::Type backwardsTypeUp = m_board->getPiece(x_pos, y_pos).getType();
    countArray[6] = {countBackwardsDiagonalUp(x_pos, y_pos, backwardsTypeUp), backwardsTypeUp};

    Piece::Type backwardsTypeDown = m_board->getPiece(x_pos, y_pos).getType();
    countArray[7] = {countBackwardsDiagonalDown(x_pos, y_pos, backwardsTypeDown), backwardsTypeDown};
    
    // Backwards up+down
    // Have to account for (x_pos, y_pos) being counted twice!
    countArray[8] = (backwardsTypeUp != Piece::Empty) && (backwardsTypeUp == backwardsTypeDown) ?
        (struct Streak){countArray[6].count + countArray[7].count-1, backwardsTypeUp}
            : (struct Streak){0, Piece::Empty};

    // Down
    Piece::Type downType = m_board->getPiece(x_pos, y_pos).getType();
    countArray[9] = {countDown(x_pos, y_pos, downType), downType};

    // return {0, Piece::Empty};
    auto max = std::max_element(countArray.begin(), countArray.end(), [](const Streak& a, const Streak& b){ return a.count < b.count; });

    return *max;
}

QuickValidator::Streak QuickValidator::getStreak(int x_pos)
{
    std::array<Streak,10> countArray = {};
    // get the top of
    int y_pos = m_board->getTopOfColumns()[x_pos];

    // Left
    Piece::Type leftType = m_board->getPiece(x_pos-1, y_pos).getType();
    countArray[0] = {countLeft(x_pos-1, y_pos, leftType) + 1, leftType};

    // Right
    Piece::Type rightType = m_board->getPiece(x_pos+1, y_pos).getType();
    countArray[1] = {countRight(x_pos+1, y_pos, rightType) + 1, rightType};
    
    // Left+Right
    countArray[2] = (leftType != Piece::Empty) && (leftType == rightType) ? 
        (struct Streak){(countArray[0].count + countArray[1].count) + 1, leftType} 
            : (struct Streak){0, Piece::Empty};

    // Forwards Diagonal
    Piece::Type forwardsTypeUp = m_board->getPiece(x_pos+1, y_pos+1).getType();
    countArray[3] = {countForwardsDiagonalUp(x_pos+1, y_pos+1, forwardsTypeUp) + 1, forwardsTypeUp};

    Piece::Type forwardsTypeDown = m_board->getPiece(x_pos-1, y_pos-1).getType();
    countArray[4] = {countForwardsDiagonalDown(x_pos-1, y_pos-1, forwardsTypeDown) + 1, forwardsTypeDown};
    
    countArray[5] = (forwardsTypeUp != Piece::Empty) && (forwardsTypeUp == forwardsTypeDown) ?
        (struct Streak){countArray[3].count + countArray[4].count + 1, forwardsTypeUp} 
            : (struct Streak){0, Piece::Empty};

    // Backwards Digonal
    Piece::Type backwardsTypeUp = m_board->getPiece(x_pos-1, y_pos+1).getType();
    countArray[6] = {countBackwardsDiagonalUp(x_pos-1, y_pos+1, backwardsTypeUp) + 1, backwardsTypeUp};

    Piece::Type backwardsTypeDown = m_board->getPiece(x_pos+1, y_pos-1).getType();
    countArray[7] = {countBackwardsDiagonalDown(x_pos+1, y_pos-1, backwardsTypeDown) + 1, backwardsTypeDown};

    // Forwards+Backwards
    countArray[8] = (backwardsTypeUp != Piece::Empty) && (backwardsTypeUp == backwardsTypeDown) ?
        (struct Streak){countArray[6].count + countArray[7].count + 1, backwardsTypeUp}
            : (struct Streak){0, Piece::Empty};

    // Down
    Piece::Type downType = m_board->getPiece(x_pos, y_pos-1).getType();
    countArray[9] = {countDown(x_pos, y_pos-1, downType) + 1, downType};

  
    auto max = std::max_element(countArray.begin(), countArray.end(), [](const Streak& a, const Streak& b){ return a.count < b.count; });

    return *max;

}

inline int QuickValidator::countLeft(int origin_x, int origin_y, Piece::Type currentPieceType)
{
    int count = 0;
    if(currentPieceType == Piece::Empty)
    {
        return count;
    }

    if(m_board->getPiece(origin_x, origin_y).getType() == currentPieceType) 
    {
        count++;
        if(m_board->getPiece(origin_x - 1, origin_y).getType() == currentPieceType)
        {
            count++;
            if(m_board->getPiece(origin_x - 2, origin_y).getType() == currentPieceType)
            {
                count++;
                if(m_board->getPiece(origin_x - 3, origin_y).getType() == currentPieceType)
                {
                    count++;
                }
            }
        }
    }
    return count;
}

inline int QuickValidator::countRight(int origin_x, int origin_y, Piece::Type currentPieceType)
{
    int count = 0;
    if(currentPieceType == Piece::Empty)
    {
        return count;
    }

    if(m_board->getPiece(origin_x, origin_y).getType() == currentPieceType) 
    {
        count++;
        if(m_board->getPiece(origin_x + 1, origin_y).getType() == currentPieceType)
        {
            count++;
            if(m_board->getPiece(origin_x + 2, origin_y).getType() == currentPieceType)
            {
                count++;
                if(m_board->getPiece(origin_x + 3, origin_y).getType() == currentPieceType)
                {
                    count++;
                }
            }
        }
    }
    return count;
}

inline int QuickValidator::countForwardsDiagonalUp(int origin_x, int origin_y, Piece::Type currentPieceType)
{
    int count = 0;
    if(currentPieceType == Piece::Empty)
    {
        return count;
    }
    
    if(m_board->getPiece(origin_x, origin_y).getType() == currentPieceType) 
    {
        count++;
        if(m_board->getPiece(origin_x + 1, origin_y + 1).getType() == currentPieceType)
        {
            count++;
            if(m_board->getPiece(origin_x + 2, origin_y + 2).getType() == currentPieceType)
            {
                count++;
                if(m_board->getPiece(origin_x + 3, origin_y + 3).getType() == currentPieceType)
                {
                    count++;
                }
            }
        }
    }
    return count;
}

inline int QuickValidator::countForwardsDiagonalDown(int origin_x, int origin_y, Piece::Type currentPieceType)
{
    int count = 0;
    if(currentPieceType == Piece::Empty)
    {
        return count;
    }

    if(m_board->getPiece(origin_x, origin_y).getType() == currentPieceType) 
    {
        count++;
        if(m_board->getPiece(origin_x - 1, origin_y - 1).getType() == currentPieceType)
        {
            count++;
            if(m_board->getPiece(origin_x - 2, origin_y - 2).getType() == currentPieceType)
            {
                count++;
                if(m_board->getPiece(origin_x - 3, origin_y - 3).getType() == currentPieceType)
                {
                    count++;
                }
            }
        }
    }
    return count;
}

inline int QuickValidator::countBackwardsDiagonalUp(int origin_x, int origin_y, Piece::Type currentPieceType)
{
    int count = 0;
    if(currentPieceType == Piece::Empty)
    {
        return count;
    }

    if(m_board->getPiece(origin_x, origin_y).getType() == currentPieceType) 
    {
        count++;
        if(m_board->getPiece(origin_x - 1, origin_y + 1).getType() == currentPieceType)
        {
            count++;
            if(m_board->getPiece(origin_x - 2, origin_y + 2).getType() == currentPieceType)
            {
                count++;
                if(m_board->getPiece(origin_x - 3, origin_y + 3).getType() == currentPieceType)
                {
                    count++;
                }
            }
        }
    }
    return count;
}

inline int QuickValidator::countBackwardsDiagonalDown(int origin_x, int origin_y, Piece::Type currentPieceType)
{
    int count = 0;
    if(currentPieceType == Piece::Empty)
    {
        return count;
    }

    if(m_board->getPiece(origin_x, origin_y).getType() == currentPieceType) 
    {
        count++;
        if(m_board->getPiece(origin_x + 1, origin_y - 1).getType() == currentPieceType)
        {
            count++;
            if(m_board->getPiece(origin_x + 2, origin_y - 2).getType() == currentPieceType)
            {
                count++;
                if(m_board->getPiece(origin_x + 3, origin_y - 3).getType() == currentPieceType)
                {
                    count++;
                }
            }
        }
    }
    return count;
}

inline int QuickValidator::countDown(int origin_x, int origin_y, Piece::Type currentPieceType)
{
    int count = 0;
    if(currentPieceType == Piece::Empty)
    {
        return count;
    }

    if(m_board->getPiece(origin_x, origin_y).getType() == currentPieceType) 
    {
        count++;
        if(m_board->getPiece(origin_x, origin_y - 1).getType() == currentPieceType)
        {
            count++;
            if(m_board->getPiece(origin_x, origin_y - 2).getType() == currentPieceType)
            {
                count++;
                if(m_board->getPiece(origin_x, origin_y - 3).getType() == currentPieceType)
                {
                    count++;
                }
            }
        }
    }
    return count;
}


