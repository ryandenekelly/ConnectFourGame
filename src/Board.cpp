#include "Board.hpp"


#include <iostream>

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

bool Board::placePiece(int x_pos, Piece piece)
{
    if(piece.getType() == Piece::Empty)
    {
        return false;
    }
    if(x_pos >= m_width)
    {
        return false;
    }

    int topOfColumn = m_topOfColumns[x_pos];
    if(topOfColumn >= m_height)
    {
        return false;
    }
    m_gameBoard[x_pos][topOfColumn] = piece;
    m_topOfColumns[x_pos]++;
    return true;

    
}

Piece Board::getPiece(int x, int y)
{
    return m_gameBoard[x][y];
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