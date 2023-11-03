#ifndef COMPUTER_PLAYER_HPP
#define COMPUTER_PLAYER_HPP

#include "Player.hpp"
#include "QuickValidator.hpp"

#include <array>
#include <vector>

class ComputerPlayer : public Player
{
    public:
        ComputerPlayer();
        ComputerPlayer(Piece::Type type);
        virtual int getMove(Board * board);
        virtual int getMoveValue(QuickValidator::Streak streak);
        

        
};

class ReflexPlayer : public ComputerPlayer
{
    public:
        ReflexPlayer();

        ReflexPlayer(Piece::Type type) : ComputerPlayer(type) {};
        virtual int getMove(Board * board);
        virtual int getMoveValue(QuickValidator::Streak streak);

        Piece::Type getPiece();
    
    private:
};

class MiniMaxPlayer : public ComputerPlayer
{
    public:
        MiniMaxPlayer();
        MiniMaxPlayer(Piece::Type type) : ComputerPlayer(type) {};

        struct Node
        {
            int column;
            int value;
        };

        virtual int getMove(Board * board);
        virtual int getMoveValue(QuickValidator::Streak streak);

        Node minimax(Board * board, int node, int depth, int alpha, int beta, bool maxPlayer);

        Piece::Type getPiece();
    private:
        int const m_treeDepth = 10;
};

#endif