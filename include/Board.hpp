#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include "Piece.hpp"

class Board
{
    public:
        Board();
        void initBoard();
        void printBoard();
        bool placePiece(int column, Piece piece);
        Piece getPiece(int x, int y);
        int getHeight();
        int getWidth();



    private:
        static constexpr int m_height = 6;
        static constexpr int m_width = 7;
        std::array<std::array<Piece, m_height>, m_width> m_gameBoard;

        
};

#endif