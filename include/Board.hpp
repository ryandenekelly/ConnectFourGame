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
        std::array<int, 7> getTopOfColumns();
        void resetBoard();

        enum ColumnStatus
        {
            ColumnFull = -1
        };



    private:
        static constexpr int m_height = 6;
        static constexpr int m_width = 7;
        std::array<std::array<Piece, m_height>, m_width> m_gameBoard;
        std::array<int,7> m_topOfColumns;

        inline static const std::string TOP_BORDER  = " _____________________\n";
        inline static const std::string BOTTOM_BORDER = "  0  1  2  3  4  5  6\n\n";
        
};

#endif