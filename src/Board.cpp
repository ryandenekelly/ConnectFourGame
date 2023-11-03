#include "Board.hpp"


#include <iostream>
#include <vector>

Board::Board()
{
    // Create the 2d-array for the gameboard
    std::array<std::array<Piece, m_width>, m_height> m_gameBoard = {{}};

    // Initialise the gameboard.
    initBoard();

    m_topOfColumns = {};

}

void Board::initBoard()
{
    // Create an empty Piece object to polulate the board.
    Piece empty = Piece(Piece::Empty);

    // Create a row of empty pieces.
    std::array<Piece, m_height> column = {{empty, empty, empty, empty, empty, empty}};

    // Create the gameboard using the empty rows.
    std::array<std::array<Piece, m_height>, m_width> board = {{column, column, column, column, column, column, column}};
    m_gameBoard = board;

}

void Board::printBoard()
{
    // Top border.
    std::cout << TOP_BORDER;
    for(int y_pos=m_height-1; y_pos>=0; y_pos--)
    {
        // Left border.
        std::cout << "|";

        // Print the appropriate symbol for each piece.
        for(int x_pos=0; x_pos<m_width; x_pos++)
        {
            if( m_gameBoard[x_pos][y_pos].getType() == Piece::Blue)
            {
                std::cout << " \033[1;34mⵔ\033[0m ";
            }
            else if( m_gameBoard[x_pos][y_pos].getType() == Piece::Red)
            {
                std::cout << " \033[1;31mⵔ\033[0m ";
            }
            else
            {
                std::cout << " . ";
            }
            
        }
        // Write border - new row
        std::cout << "|\n";
    }
    // Bottom border.
    std::cout << BOTTOM_BORDER;

}

bool Board::checkMove(int move)
{
    if(move >= m_width || move < 0)
    {
        return false;
    }
    int topOfColumn = m_topOfColumns[move];
    if(topOfColumn >= m_height || topOfColumn == ColumnFull)
    {
        return false;
    }
    return true;
}
bool Board::placePiece(int x_pos, Piece piece)
{
    if(piece.getType() == Piece::Empty)
    {
        return false;
    }

    int topOfColumn = m_topOfColumns[x_pos];
    if(topOfColumn >= m_height)
    {
        m_topOfColumns[x_pos] = ColumnFull;
        return false;
    }
    else
    {
        m_gameBoard[x_pos][topOfColumn] = piece;
        m_topOfColumns[x_pos]++;
    }
    
    m_boardFull = ++m_totalPieces == m_height*m_width;

    return true;

    
}

Piece Board::getPiece(int x, int y)
{
    if( (x>=0 && x<m_width) && (y>=0 && y<m_height) )
    {
        return m_gameBoard[x][y];
    }
    return Piece::Empty;
}

int Board::getHeight()
{
    return m_height;
}

int Board::getWidth()
{
    return m_width;
}

std::array<int,7> Board::getTopOfColumns()
{
    return m_topOfColumns;
}

std::vector<int> Board::getLegalMoves()
{
    std::vector<int> legalMoves;
    for(int i=0; i<m_topOfColumns.size(); i++)
    {
        if(m_topOfColumns[i] != Board::ColumnFull && m_topOfColumns[i] < 6)
        {
           legalMoves.push_back(i); 
        }
        
    }
    return legalMoves;
}

void Board::resetBoard()
{
    // Reset "stack pointers".
    std::fill(m_topOfColumns.begin(), m_topOfColumns.end(), Piece::Empty);
    
    // Reset board by columns.
    for(auto& a : m_gameBoard)
    {
        std::fill(a.begin(), a.end(), Piece::Empty);
    }
}

bool Board::isBoardFull()
{
    return m_boardFull;
}