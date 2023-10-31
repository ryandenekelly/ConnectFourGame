#include "QuickValidator.hpp"
#include <algorithm>

QuickValidator::QuickValidator(Board * board)
{
    m_board = board;
}


int QuickValidator::getStreak(int x_pos)
{
    std::array<int,10> countArray = {};
    // get the top of
    int y_pos = m_board->getTopOfColumns()[x_pos];

    // Left
    Piece::Type leftType = m_board->getPiece(x_pos-1, y_pos).getType();
    countArray[0] = countLeft(x_pos-1, y_pos, leftType);

    // Right
    Piece::Type rightType = m_board->getPiece(x_pos+1, y_pos).getType();
    countArray[1] = countRight(x_pos+1, y_pos, rightType);
    
    // Left+Right
    countArray[2] = leftType == rightType ? countArray[0] + countArray[1] : 0;

    // Forwards Diagonal
    Piece::Type forwardsTypeUp = m_board->getPiece(x_pos+1, y_pos+1).getType();
    countArray[3] = countForwardsDiagonalUp(x_pos+1, y_pos+1, forwardsTypeUp);

    Piece::Type forwardsTypeDown = m_board->getPiece(x_pos-1, y_pos-1).getType();
    countArray[4] = countForwardsDiagonalDown(x_pos-1, y_pos-1, forwardsTypeDown);
    
    countArray[5] = forwardsTypeUp == forwardsTypeDown ? countArray[3] + countArray[4] : 0;

    // Backwards Digonal
    Piece::Type backwardsTypeUp = m_board->getPiece(x_pos-1, y_pos+1).getType();
    countArray[6] = countBackwardsDiagonalUp(x_pos-1, y_pos+1, backwardsTypeUp);

    Piece::Type backwardsTypeDown = m_board->getPiece(x_pos+1, y_pos-1).getType();
    countArray[7] = countBackwardsDiagonalDown(x_pos+1, y_pos-1, backwardsTypeDown);

    // Forwards+Backwards
    countArray[8] = backwardsTypeUp == backwardsTypeDown ? countArray[6] + countArray[7] : 0;

    // Down
    Piece::Type downType = m_board->getPiece(x_pos, y_pos-1).getType();
    countArray[9] = countDown(x_pos, y_pos-1, downType);


    auto max = std::max_element(countArray.begin(), countArray.end());

    return *max;
}

int QuickValidator::getStreakGeneric(int x_pos)
{
    std::array<int,10> countArray = {};
    // get the top of
    int y_pos = m_board->getTopOfColumns()[x_pos];

    // Left
    Piece::Type leftType = m_board->getPiece(x_pos-1, y_pos).getType();
    countArray[0] = countGeneric(x_pos-1, y_pos, leftType, Left);

    // Right
    Piece::Type rightType = m_board->getPiece(x_pos+1, y_pos).getType();
    countArray[1] = countGeneric(x_pos+1, y_pos, rightType, Right);
    
    // Left+Right
    countArray[2] = leftType == rightType ? countArray[0] + countArray[1] : 0;

    // Forwards Diagonal
    Piece::Type forwardsTypeUp = m_board->getPiece(x_pos+1, y_pos+1).getType();
    countArray[3] = countGeneric(x_pos+1, y_pos+1, forwardsTypeUp, ForwardsUp);

    Piece::Type forwardsTypeDown = m_board->getPiece(x_pos-1, y_pos-1).getType();
    countArray[4] = countGeneric(x_pos-1, y_pos-1, forwardsTypeDown, ForwardsDown);
    
    countArray[5] = forwardsTypeUp == forwardsTypeDown ? countArray[3] + countArray[4] : 0;

    // Backwards Digonal
    Piece::Type backwardsTypeUp = m_board->getPiece(x_pos-1, y_pos+1).getType();
    countArray[6] = countGeneric(x_pos-1, y_pos+1, backwardsTypeUp, BackwardsUp);

    Piece::Type backwardsTypeDown = m_board->getPiece(x_pos+1, y_pos-1).getType();
    countArray[7] = countGeneric(x_pos+1, y_pos-1, backwardsTypeDown, BackwardsDown);

    // Forwards+Backwards
    countArray[8] = backwardsTypeUp == backwardsTypeDown ? countArray[6] + countArray[7] : 0;

    // Down
    Piece::Type downType = m_board->getPiece(x_pos, y_pos-1).getType();
    countArray[9] = countGeneric(x_pos, y_pos-1, downType, Down);


    auto max = std::max_element(countArray.begin(), countArray.end());

    return *max;
}

inline int QuickValidator::countGeneric(int origin_x, int origin_y, Piece::Type currentPieceType, QuickValidator::Direction direction)
{
    int count = 0;
    if(currentPieceType == Piece::Empty)
    {
        return count;
    }
    count++;
    if( (m_board->getPiece(getExpressionX(origin_x, 1, direction), getExpressionY(origin_y, 1, direction)).getType() == currentPieceType && ++count) 
        && (m_board->getPiece(getExpressionX(origin_x, 2, direction), getExpressionY(origin_y, 2, direction)).getType() == currentPieceType && ++count) )
    {   
        return count;
    }
    return count;
}
inline int QuickValidator::countLeft(int origin_x, int origin_y, Piece::Type currentPieceType)
{
    int count = 0;
    if(currentPieceType == Piece::Empty)
    {
        return count;
    }
    count++;
    if( (m_board->getPiece(origin_x - 1, origin_y).getType() == currentPieceType && ++count) 
        && (m_board->getPiece(origin_x - 2, origin_y).getType() == currentPieceType && ++count) )
    {   
        return count;
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
    count++;
    if( (m_board->getPiece(origin_x + 1, origin_y).getType() == currentPieceType && ++count) 
        && (m_board->getPiece(origin_x + 2, origin_y).getType() == currentPieceType && ++count) )
    {   
        return count;
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
    count++;
    if( (m_board->getPiece(origin_x + 1, origin_y + 1).getType() == currentPieceType && ++count) 
        && (m_board->getPiece(origin_x + 2, origin_y + 2).getType() == currentPieceType && ++count) )
    {   
        return ++count;
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
    count++;
    if( (m_board->getPiece(origin_x - 1, origin_y - 1).getType() == currentPieceType && ++count) 
        && (m_board->getPiece(origin_x - 2, origin_y - 2).getType() == currentPieceType && ++count) )
    {   
        return ++count;
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
    count++;
    if((m_board->getPiece(origin_x - 1, origin_y + 1).getType() == currentPieceType && ++count) 
        && (m_board->getPiece(origin_x - 2, origin_y + 2).getType() == currentPieceType && ++count) )
    {   
        return ++count;
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
    count++;
    if((m_board->getPiece(origin_x + 1, origin_y - 1).getType() == currentPieceType && ++count) 
        && (m_board->getPiece(origin_x + 2, origin_y - 2).getType() == currentPieceType && ++count) )
    {   
        return ++count;
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
    count++;
    if( (m_board->getPiece(origin_x, origin_y - 1).getType() == currentPieceType && ++count) 
        && (m_board->getPiece(origin_x , origin_y - 2).getType() == currentPieceType && ++count) )
    {   
        return ++count;
    }
    return count;
}

inline int QuickValidator::getExpressionX(int origin_x, int step, QuickValidator::Direction direction)
{
    switch(direction)
    {
        case QuickValidator::Left:
        case QuickValidator::ForwardsDown:
        case QuickValidator::BackwardsUp:
            return origin_x - (1*step);

        case QuickValidator::Right:
        case QuickValidator::ForwardsUp:
        case QuickValidator::BackwardsDown:
            return origin_x + (1*step);

        case QuickValidator::Down:
            return origin_x;
            
        default:
            return -1;
    }
}

inline int QuickValidator::getExpressionY(int origin_y, int step, QuickValidator::Direction direction)
{
    switch(direction)
    {
        case QuickValidator::Left:
        case QuickValidator::Right:
            return origin_y;
        case QuickValidator::ForwardsUp:
        case QuickValidator::BackwardsUp:
            return origin_y + (1 * step);
        case QuickValidator::ForwardsDown:
        case QuickValidator::BackwardsDown:
        case QuickValidator::Down:
            return origin_y - (1 * step);

        default:
            return -1;

    }
}


