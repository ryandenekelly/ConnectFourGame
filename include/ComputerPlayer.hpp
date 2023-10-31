#ifndef COMPUTER_PLAYER_HPP
#define COMPUTER_PLAYER_HPP

#include "Player.hpp"

#include <array>
#include <vector>

class ComputerPlayer : public Player
{
    public:
        ComputerPlayer();
        ComputerPlayer(Piece::Type type);
        virtual int getMove(Board * board);

        Piece::Type getPiece();

        
};

class ReflexPlayer : public ComputerPlayer
{
    public:
        ReflexPlayer();

        ReflexPlayer(Piece::Type type) : ComputerPlayer(type) {};
        virtual int getMove(Board * board);
        int getMoveValue(std::vector<std::pair<Piece::Type, int>> streaks);

        Piece::Type getPiece();
    
    private:
};

class MiniMaxPlayer : public ComputerPlayer
{
    public:
        // MiniMaxPlayer();
        // MiniMaxPlayer(Piece::Type type);
        // virtual int getMove(Board * board);
};

class ExpMaxPlayer : public ComputerPlayer
{
    public:
        // ExpMaxPlayer();
        // ExpMaxPlayer(Piece::Type type);
        // virtual int getMove(Board * board);
};

#endif